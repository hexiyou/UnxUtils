$ ! Set the LOGICAL SYS to SYS$LIBRARY if it isn't defined
$ ! so that #include <sys/...> will search SYS$LIBRARY for the file.
$ IF F$TRNLNM("SYS") .EQS. "" THEN DEFINE SYS SYS$LIBRARY
$ WRITE SYS$OUTPUT "Compiling ALLOCA..."
$ CC ALLOCA.C   /DEFINE=(HAVE_STRING_H,HAVE_MEMCHR,HAVE_STRERROR)
$ WRITE SYS$OUTPUT "Compiling DFA..."
$ CC DFA.C      /DEFINE=(HAVE_STRING_H,HAVE_MEMCHR,HAVE_STRERROR)
$ WRITE SYS$OUTPUT "Compiling GETOPT..."
$ CC GETOPT.C   /DEFINE=(HAVE_STRING_H,HAVE_MEMCHR,HAVE_STRERROR)
$ WRITE SYS$OUTPUT "Compiling GETOPT1..."
$ CC GETOPT1.C   /DEFINE=(HAVE_STRING_H,HAVE_MEMCHR,HAVE_STRERROR)
$ WRITE SYS$OUTPUT "Compiling GREP..."
$ CC GREP.C     /DEFINE=(HAVE_STRING_H,HAVE_MEMCHR,HAVE_STRERROR, -
             VERSION="2.3.1",initialize_main="vms_fab")
$ WRITE SYS$OUTPUT "Compiling KWSET..."
$ CC KWSET.C    /DEFINE=(HAVE_STRING_H,HAVE_MEMCHR,HAVE_STRERROR)
$ WRITE SYS$OUTPUT "Compiling OBSTACK..."
$ CC OBSTACK.C  /DEFINE=(HAVE_STRING_H,HAVE_MEMCHR,HAVE_STRERROR)
$ WRITE SYS$OUTPUT "Compiling REGEX..."
$ CC REGEX.C    /DEFINE=(HAVE_STRING_H,HAVE_MEMCHR,HAVE_STRERROR)
$ WRITE SYS$OUTPUT "Compiling SEARCH..."
$ CC SEARCH.C   /DEFINE=(HAVE_STRING_H,HAVE_MEMCHR,HAVE_STRERROR)
$ WRITE SYS$OUTPUT "Compiling VMS_FAB..."
$ CC VMS_FAB.C   /DEFINE=(HAVE_STRING_H,HAVE_MEMCHR,HAVE_STRERROR)
$ WRITE SYS$OUTPUT "Compiling GREPMAT..."
$ CC GREPMAT.C   /DEFINE=(HAVE_STRING_H,HAVE_MEMCHR,HAVE_STRERROR)
$ WRITE SYS$OUTPUT "Linking GREP..."
$ LINK GREP,ALLOCA,DFA,GETOPT,GETOPT1,KWSET,OBSTACK,REGEX,SEARCH,VMS_FAB,GREPMAT
$ WRITE SYS$OUTPUT "Compiling EGREPMAT..."
$ CC EGREPMAT.C   /DEFINE=(HAVE_STRING_H,HAVE_MEMCHR,HAVE_STRERROR)
$ WRITE SYS$OUTPUT "Linking EGREP..."
$ LINK EGREP,ALLOCA,DFA,GETOPT,GETOPT1,KWSET,OBSTACK,REGEX,SEARCH,VMS_FAB,EGREPMAT
$ CC FGREPMAT.C   /DEFINE=(HAVE_STRING_H,HAVE_MEMCHR,HAVE_STRERROR)
$ WRITE SYS$OUTPUT "Linking FGREP..."
$ LINK FGREP,ALLOCA,DFA,GETOPT,GETOPT1,KWSET,OBSTACK,REGEX,SEARCH,VMS_FAB,FGREPMAT
$ EXIT
