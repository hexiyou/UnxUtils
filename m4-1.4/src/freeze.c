/* GNU m4 -- A simple macro processor
   Copyright (C) 1989, 90, 91, 92, 93, 94 Free Software Foundation, Inc.
  
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.
  
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
  
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/* This module handles frozen files.  */

#include "m4.h"

/*-------------------------------------------------------------------.
| Destructively reverse a symbol list and return the reversed list.  |
`-------------------------------------------------------------------*/

static symbol *
reverse_symbol_list (symbol *sym)
{
  symbol *result;
  symbol *next;

  result = NULL;
  while (sym)
    {
      next = SYMBOL_NEXT (sym);
      SYMBOL_NEXT (sym) = result;
      result = sym;
      sym = next;
    }
  return result;
}

/*------------------------------------------------.
| Produce a frozen state to the given file NAME.  |
`------------------------------------------------*/

void
produce_frozen_state (const char *name)
{
  FILE *file;
  int h;
  symbol *sym;
  const builtin *bp;

  if (file = fopen (name, "w"), !file)
    {
      M4ERROR ((warning_status, errno, name));
      return;
    }

  /* Write a recognizable header.  */

  fprintf (file, "# This is a frozen state file generated by GNU %s %s\n",
	   PRODUCT, VERSION);
  fprintf (file, "V1\n");

  /* Dump quote delimiters.  */

  if (strcmp (lquote.string, DEF_LQUOTE) || strcmp (rquote.string, DEF_RQUOTE))
    {
      fprintf (file, "Q%d,%d\n", (int) lquote.length, (int) rquote.length);
      fputs (lquote.string, file);
      fputs (rquote.string, file);
      fputc ('\n', file);
    }

  /* Dump comment delimiters.  */

  if (strcmp (bcomm.string, DEF_BCOMM) || strcmp (ecomm.string, DEF_ECOMM))
    {
      fprintf (file, "C%d,%d\n", (int) bcomm.length, (int) ecomm.length);
      fputs (bcomm.string, file);
      fputs (ecomm.string, file);
      fputc ('\n', file);
    }

  /* Dump all symbols.  */

  for (h = 0; h < hash_table_size; h++)
    {

      /* Process all entries in one bucket, from the last to the first.
	 This order ensures that, at reload time, pushdef's will be
	 executed with the oldest definitions first.  */

      symtab[h] = reverse_symbol_list (symtab[h]);
      for (sym = symtab[h]; sym; sym = SYMBOL_NEXT (sym))
	{
	  switch (SYMBOL_TYPE (sym))
	    {
	    case TOKEN_TEXT:
	      fprintf (file, "T%d,%d\n",
		       (int) strlen (SYMBOL_NAME (sym)),
		       (int) strlen (SYMBOL_TEXT (sym)));
	      fputs (SYMBOL_NAME (sym), file);
	      fputs (SYMBOL_TEXT (sym), file);
	      fputc ('\n', file);
	      break;

	    case TOKEN_FUNC:
	      bp = find_builtin_by_addr (SYMBOL_FUNC (sym));
	      if (bp == NULL)
		{
		  M4ERROR ((warning_status, 0, "\
INTERNAL ERROR: Built-in not found in builtin table!"));
		  abort ();
		}
	      fprintf (file, "F%d,%d\n",
		       (int) strlen (SYMBOL_NAME (sym)),
		       (int) strlen (bp->name));
	      fputs (SYMBOL_NAME (sym), file);
	      fputs (bp->name, file);
	      fputc ('\n', file);
	      break;

	    default:
	      M4ERROR ((warning_status, 0, "\
INTERNAL ERROR: Bad token data type in freeze_one_symbol ()"));
	      abort ();
	      break;
	    }
	}

      /* Reverse the bucket once more, putting it back as it was.  */

      symtab[h] = reverse_symbol_list (symtab[h]);
    }

  /* Let diversions be issued from output.c module, its cleaner to have this
     piece of code there.  */

  freeze_diversions (file);

  /* All done.  */

  fputs ("# End of frozen state file\n", file);
  fclose (file);
}

/*----------------------------------------------------------------------.
| Issue a message saying that some character is an EXPECTED character.  |
`----------------------------------------------------------------------*/

static void
issue_expect_message (int expected)
{
  if (expected == '\n')
    M4ERROR ((EXIT_FAILURE, 0, "Expecting line feed in frozen file"));
  else
    M4ERROR ((EXIT_FAILURE, 0, "Expecting character `%c' in frozen file",
	      expected));
}

/*-------------------------------------------------.
| Reload a frozen state from the given file NAME.  |
`-------------------------------------------------*/

/* We are seeking speed, here.  */

void
reload_frozen_state (const char *name)
{
  FILE *file;
  int character;
  int operation;
  char *string[2];
  int allocated[2];
  int number[2];
  const builtin *bp;

#define GET_CHARACTER \
  (character = getc (file))

#define GET_NUMBER(Number) \
  do								\
    {								\
      (Number) = 0;						\
      while (isdigit (character))				\
	{							\
	  (Number) = 10 * (Number) + character - '0';		\
	  GET_CHARACTER;					\
	}							\
    }								\
  while (0)

#define VALIDATE(Expected) \
  do								\
    {								\
      if (character != (Expected))				\
	issue_expect_message ((Expected));			\
    }								\
  while (0)

  file = path_search (name);
  if (file == NULL)
    M4ERROR ((EXIT_FAILURE, errno, "Cannot open %s", name));

  allocated[0] = 100;
  string[0] = xmalloc ((size_t) allocated[0]);
  allocated[1] = 100;
  string[1] = xmalloc ((size_t) allocated[1]);

  while (GET_CHARACTER, character != EOF)
    switch (character)
      {
      default:
	M4ERROR ((EXIT_FAILURE, 0, "Ill-formated frozen file"));

      case '\n':

	/* Skip empty lines.  */

	break;

      case '#':

	/* Comments are introduced by `#' at beginning of line, and are
	   ignored.  */

	while (character != EOF && character != '\n')
	  GET_CHARACTER;
	VALIDATE ('\n');
	break;

      case 'C':
      case 'D':
      case 'F':
      case 'T':
      case 'Q':
	operation = character;
	GET_CHARACTER;

	/* Get string lengths.  Accept a negative diversion number.  */

	if (operation == 'D' && character == '-')
	  {
	    GET_CHARACTER;
	    GET_NUMBER (number[0]);
	    number[0] = -number[0];
	  }
	else
	  GET_NUMBER (number[0]);
	VALIDATE (',');
	GET_CHARACTER;
	GET_NUMBER (number[1]);
	VALIDATE ('\n');

	if (operation != 'D')
	  {
	    
	    /* Get first string contents.  */

	    if (number[0] + 1 > allocated[0])
	      {
		free (string[0]);
		allocated[0] = number[0] + 1;
		string[0] = xmalloc ((size_t) allocated[0]);
	      }

	    if (number[0] > 0)
	      if (!fread (string[0], (size_t) number[0], 1, file))
		M4ERROR ((EXIT_FAILURE, 0, "Premature end of frozen file"));

	    string[0][number[0]] = '\0';
	  }

	/* Get second string contents.  */

	if (number[1] + 1 > allocated[1])
	  {
	    free (string[1]);
	    allocated[1] = number[1] + 1;
	    string[1] = xmalloc ((size_t) allocated[1]);
	  }

	if (number[1] > 0)
	  if (!fread (string[1], (size_t) number[1], 1, file))
	    M4ERROR ((EXIT_FAILURE, 0, "Premature end of frozen file"));

	string[1][number[1]] = '\0';
	GET_CHARACTER;
	VALIDATE ('\n');
      
	/* Act according to operation letter.  */

	switch (operation)
	  {
	  case 'C':

	    /* Change comment strings.  */

	    set_comment (string[0], string[1]);
	    break;

	  case 'D':

	    /* Select a diversion and add a string to it.  */

	    make_diversion (number[0]);
	    if (number[1] > 0)
	      shipout_text (NULL, string[1], number[1]);
	    break;

	  case 'F':

	    /* Enter a macro having a builtin function as a definition.  */

	    bp = find_builtin_by_name (string[1]);
	    if (bp)
	      define_builtin (string[0], bp, SYMBOL_PUSHDEF, 0);
	    else
	      M4ERROR ((warning_status, 0, "\
`%s' from frozen file not found in builtin table!",
			string[0]));
	    break;

	  case 'T':

	    /* Enter a macro having an expansion text as a definition.  */

	    define_user_macro (string[0], string[1], SYMBOL_PUSHDEF);
	    break;

	  case 'Q':

	    /* Change quote strings.  */

	    set_quotes (string[0], string[1]);
	    break;

	  default:

	    /* Cannot happen.  */

	    break;
	  }
	break;
	
      case 'V':

	/* Validate format version.  Only `1' is acceptable for now.  */

	GET_CHARACTER;
	VALIDATE ('1');
	GET_CHARACTER;
	VALIDATE ('\n');
	break;

      }

  free (string[0]);
  free (string[1]);
  fclose (file);

#undef GET_CHARACTER
#undef GET_NUMBER
#undef VALIDATE
}
