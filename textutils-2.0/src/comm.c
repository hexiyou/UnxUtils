/* comm -- compare two sorted files line by line.
   Copyright (C) 86, 90, 91, 1995-1999 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

/* Written by Richard Stallman and David MacKenzie. */

#include <config.h>

#include <stdio.h>
#include <getopt.h>
#include <sys/types.h>
#include "system.h"
#include "linebuffer.h"
#include "error.h"
#include "hard-locale.h"
#include "memcoll.h"

/* The official name of this program (e.g., no `g' prefix).  */
#define PROGRAM_NAME "comm"

#define AUTHORS "Richard Stallman and David MacKenzie"

/* Undefine, to avoid warning about redefinition on some systems.  */
#undef min
#define min(x, y) ((x) < (y) ? (x) : (y))

/* The name this program was run with. */
char *program_name;

#ifdef ENABLE_NLS
/* Nonzero if the LC_COLLATE locale is hard.  */
static int hard_LC_COLLATE;
#endif

/* If nonzero, print lines that are found only in file 1. */
static int only_file_1;

/* If nonzero, print lines that are found only in file 2. */
static int only_file_2;

/* If nonzero, print lines that are found in both files. */
static int both;

static struct option const long_options[] =
{
  {GETOPT_HELP_OPTION_DECL},
  {GETOPT_VERSION_OPTION_DECL},
  {0, 0, 0, 0}
};



void
usage (int status)
{
  if (status != 0)
    fprintf (stderr, _("Try `%s --help' for more information.\n"),
	     program_name);
  else
    {
      printf (_("\
Usage: %s [OPTION]... LEFT_FILE RIGHT_FILE\n\
"),
	      program_name);
      printf (_("\
Compare sorted files LEFT_FILE and RIGHT_FILE line by line.\n\
\n\
  -1              suppress lines unique to left file\n\
  -2              suppress lines unique to right file\n\
  -3              suppress lines unique to both files\n\
      --help      display this help and exit\n\
      --version   output version information and exit\n\
"));
      puts (_("\nReport bugs to <bug-textutils@gnu.org>."));
    }
  exit (status == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

/* Output the line in linebuffer LINE to stream STREAM
   provided the switches say it should be output.
   CLASS is 1 for a line found only in file 1,
   2 for a line only in file 2, 3 for a line in both. */

static void
writeline (struct linebuffer *line, FILE *stream, int class)
{
  switch (class)
    {
    case 1:
      if (!only_file_1)
	return;
      break;

    case 2:
      if (!only_file_2)
	return;
      /* Skip the tab stop for case 1, if we are printing case 1.  */
      if (only_file_1)
	putc ('\t', stream);
      break;

    case 3:
      if (!both)
	return;
      /* Skip the tab stop for case 1, if we are printing case 1.  */
      if (only_file_1)
	putc ('\t', stream);
      /* Skip the tab stop for case 2, if we are printing case 2.  */
      if (only_file_2)
	putc ('\t', stream);
      break;
    }

  fwrite (line->buffer, sizeof (char), line->length, stream);
}

/* Compare INFILES[0] and INFILES[1].
   If either is "-", use the standard input for that file.
   Assume that each input file is sorted;
   merge them and output the result.
   Return 0 if successful, 1 if any errors occur. */

static int
compare_files (char **infiles)
{
  /* For each file, we have one linebuffer in lb1.  */
  struct linebuffer lb1[2];

  /* thisline[i] points to the linebuffer holding the next available line
     in file i, or is NULL if there are no lines left in that file.  */
  struct linebuffer *thisline[2];

  /* streams[i] holds the input stream for file i.  */
  FILE *streams[2];

  int i, ret = 0;

  /* Initialize the storage. */
  for (i = 0; i < 2; i++)
    {
      initbuffer (&lb1[i]);
      thisline[i] = &lb1[i];
      streams[i] = (STREQ (infiles[i], "-") ? stdin : fopen (infiles[i], "r"));
      if (!streams[i])
	{
	  error (0, errno, "%s", infiles[i]);
	  return 1;
	}

      thisline[i] = readline (thisline[i], streams[i]);
    }

  while (thisline[0] || thisline[1])
    {
      int order;

      /* Compare the next available lines of the two files.  */

      if (!thisline[0])
	order = 1;
      else if (!thisline[1])
	order = -1;
      else
	{
#ifdef ENABLE_NLS
	  if (hard_LC_COLLATE)
	    order = memcoll (thisline[0]->buffer, thisline[0]->length,
			     thisline[1]->buffer, thisline[1]->length);
	  else
#endif
	    {
	      order = memcmp (thisline[0]->buffer, thisline[1]->buffer,
			      min (thisline[0]->length, thisline[1]->length));
	      if (order == 0)
		order = thisline[0]->length - thisline[1]->length;
	    }
	}

      /* Output the line that is lesser. */
      if (order == 0)
	writeline (thisline[1], stdout, 3);
      else if (order > 0)
	writeline (thisline[1], stdout, 2);
      else
	writeline (thisline[0], stdout, 1);

      /* Step the file the line came from.
	 If the files match, step both files.  */
      if (order >= 0)
	thisline[1] = readline (thisline[1], streams[1]);
      if (order <= 0)
	thisline[0] = readline (thisline[0], streams[0]);
    }

  /* Free all storage and close all input streams. */
  for (i = 0; i < 2; i++)
    {
      free (lb1[i].buffer);
      if (ferror (streams[i]) || fclose (streams[i]) == EOF)
	{
	  error (0, errno, "%s", infiles[i]);
	  ret = 1;
	}
    }
  if (ferror (stdout) || fclose (stdout) == EOF)
    {
      error (0, errno, _("write error"));
      ret = 1;
    }
  return ret;
}

int
main (int argc, char **argv)
{
  int c;

  program_name = argv[0];
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, "/usr/local/share/locale");
  textdomain (PACKAGE);

#ifdef ENABLE_NLS
  hard_LC_COLLATE = hard_locale (LC_COLLATE);
#endif

  only_file_1 = 1;
  only_file_2 = 1;
  both = 1;

  while ((c = getopt_long (argc, argv, "123", long_options, NULL)) != -1)
    switch (c)
      {
      case 0:
	break;

      case '1':
	only_file_1 = 0;
	break;

      case '2':
	only_file_2 = 0;
	break;

      case '3':
	both = 0;
	break;

      case_GETOPT_HELP_CHAR;

      case_GETOPT_VERSION_CHAR (PROGRAM_NAME, AUTHORS);

      default:
	usage (1);
      }

  if (optind + 2 != argc)
    usage (1);

  exit (compare_files (argv + optind) == 0
	? EXIT_SUCCESS : EXIT_FAILURE);
}
