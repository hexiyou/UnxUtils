/* sleep - delay for a specified amount of time.
   Copyright (C) 84, 91, 92, 93, 1994 Free Software Foundation, Inc.

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
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#ifdef HAVE_CONFIG_H
#if defined (CONFIG_BROKETS)
/* We use <config.h> instead of "config.h" so that a compilation
   using -I. -I$srcdir will use ./config.h rather than $srcdir/config.h
   (which it would do because it found this file in $srcdir).  */
#include <config.h>
#else
#include "config.h"
#endif
#endif

#include <stdio.h>
#include <sys/types.h>
#include <getopt.h>

#include "version.h"
#include "system.h"

void error ();

static long argdecode ();

/* The name by which this program was run. */
char *program_name;

/* If non-zero, display usage information and exit.  */
static int show_help;

/* If non-zero, print the version on standard output and exit.  */
static int show_version;

static struct option const long_options[] =
{
  {"help", no_argument, &show_help, 1},
  {"version", no_argument, &show_version, 1},
  {0, 0, 0, 0}
};

static void
usage (status)
     int status;
{
  if (status != 0)
    fprintf (stderr, "Try `%s --help' for more information.\n",
	     program_name);
  else
    {
      printf ("Usage: %s [OPTION]... NUMBER[SUFFIX]\n", program_name);
      printf ("\
\n\
  --help      display this help and exit\n\
  --version   output version information and exit\n\
\n\
SUFFIX may be s for seconds, m for minutes, h for hours or d for days.\n\
");
    }
  exit (status);
}

void
main (argc, argv)
     int argc;
     char **argv;
{
  int i;
  unsigned seconds = 0;
  int c;

  program_name = argv[0];

  while ((c = getopt_long (argc, argv, "", long_options, (int *) 0)) != EOF)
    {
      switch (c)
	{
	case 0:
	  break;

	default:
	  usage (1);
	}
    }

  if (show_version)
    {
      printf ("%s\n", version_string);
      exit (0);
    }

  if (show_help)
    usage (0);

  if (argc == 1)
    {
      fprintf (stderr, "Usage: %s number[smhd]...\n", argv[0]);
      exit (1);
    }

  for (i = 1; i < argc; i++)
    seconds += argdecode (argv[i]);

  sleep (seconds);

  exit (0);
}

static long
argdecode (s)
     char *s;
{
  long value;
  register char *p = s;
  register char c;

  value = 0;
  while ((c = *p++) >= '0' && c <= '9')
    value = value * 10 + c - '0';

  switch (c)
    {
    case 's':
      break;
    case 'm':
      value *= 60;
      break;
    case 'h':
      value *= 60 * 60;
      break;
    case 'd':
      value *= 60 * 60 * 24;
      break;
    default:
      p--;
    }

  if (*p)
    error (1, 0, "invalid time interval `%s'", s);
  return value;
}
