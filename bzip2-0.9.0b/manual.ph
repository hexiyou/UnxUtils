"myfile.bz2",
"rec000
&bzerror,
(2)
(INCLUDING
(bzerror
(for
(ie,
*bzerror,
*destLen
*destLen-1]
*nUnused
*strm
*strm,
, even in case of buffer overflow.
, see
, then
.  Compress from
.  If the destination buffer is big enough,
.  In the limit, it is acceptable to supply and remove data one byte at a time, although this would be terribly inefficient.  You should always ensure that at least one byte of output space is available at each call.
.bz2
/* handle error */
0.9.0
32-bit
828642
< 0 or
ADVISED
ANY
About Makertf
About this help file
Adler's
All
Allowable next actions:
Although
August
BZFILE
BZFILE* b;
BZ_DATA_ERROR
BZ_DATA_ERROR_MAGIC
BZ_FINISH
BZ_FINISH_OK
BZ_FLUSH
BZ_FLUSH_OK
BZ_IO_ERROR
BZ_IO_ERROR)
BZ_MAX_UNUSED
BZ_MEM_ERROR
BZ_NO_STDIO
BZ_OK
BZ_OK)
BZ_OUTBUFF_FULL
BZ_PARAM_ERROR
BZ_RUN
BZ_RUN_OK
BZ_SEQUENCE_END
BZ_SEQUENCE_ERROR
BZ_STREAM_END
BZ_UNEXPECTED_EOF
Because
Before each call to
Burrows
Burrows-Wheeler
CAUSED
Chapter
Compres-
Compress from
Copyright
Corpus
DATA,
DESCRIPTION
Decompres-
Digital
EVEN
Each
FILE*   f;
FINISHING.
FLUSHING
For the meaning of parameters
Further
GNU
Gailly's
H, compress with flag
However,
Huffman
I've
I/O
IMPLIED
Illegal.
Implementation
Introduction
It's
Jean-loup
Julian
LIMITED
LZ77/LZ78-based
Linux
MANAGEMENT
Makertf
Manber-Myers
Most
Multiple
NULL
Nevertheless,
Next state = F
Note
OUT
POSSIBILITY
PURPOSE
Parameter
Please
Pointer to an abstract
Possible assignments to
Possible return values:
QWF00133@niftyserve.or.jp
RUNNING
RUNNING/
Random
Rather,
Remember current value of
Return value =
Returned by
SUCH
Sadakane's
See
Seward,
Similarly,
There's
Therefore
Tsuneo
Unix
WAY
WHETHER
Wheeler
Windows
You may provide and remove as little or as much data as you like on each call of
__inline__
able
about
above
above,
above.
absolutely
abstract
accept
acceptable
action
actions
actions:
additional
after
against
algorithm
algorithm,
allocate
allocated
allocates
allocators
almost
also
always
amount
amounts
and
and/or
another
anything
appear
applications
approaches
approximately
arbitrary
are
are:
argument,
around
array
as much as possible,
as much as possible, but do not accept any more input.
asking
assertion
assignments
associated
attempt
attempts
author
autoconf
avail_in
avail_out
available
available.
avoids
basis
become
been
before
begin
behaviour
behind
below,
best
better
between
beyond
binary
block
block size.
block,
block-sorting
block.
blockSize
blockSize100k
blockSize100k,
blocks
both
buf
buf,
buffer
buffer,
buffers,
bug
bugs
built
bunzip2
but
byte
bytes
bytes),
bytes.
bzBuffToBuffCompress
bzBuffToBuffDecompress
bzCompress
bzCompressEnd
bzCompressInit
bzDecompress
bzDecompressEnd
bzDecompressInit
bzRead
bzReadClose
bzReadClose ( &bzerror, b );
bzReadGetUnused
bzReadOpen
bzWrite
bzWriteClose
bzWriteClose ( &bzerror, b );
bzWriteOpen
bz_stream
bzalloc
bzclose
bzerror
bzerror;
bzfree
bzip2
bzip2-0.1
bzip2-0.1pl2
bzip2-0.9.0
bzip2.
bzlib.h
bzlib_private.h
call
call.
called
called.
caller
calling
calls
can
can't
cannot
case
case,
cause
causes
change
changes
char    buf[ /* whatever size you like */ ];
char*         source,
check
checks
checksum,
clean
code
code.
coding.
collect
collect data from
com-
comparing
compatibility:
compile
compiled
compiler
compiler.
compiling
complete
completed
completed,
complex,
compress
compressed
compresses
compressing
compressing,      
compression
compression,
compression.
compression/decompression
compressor
compressor,
compressors,
compressors.
con-
concatenated
conditions
conducted
consider
considerably
construction
consult
contain
containing
contains
contributed
conventional
copy
correct
correctly
corresponding
corrupted
could
couple
course
create
critical
current
custom
damaged
data
data.
dealing
decision
decom-
decompress
decompress.
decompress.c
decompressed
decompresses
decompressing
decompressing, all settings normal.
decompression
decompression,
decompression.
default
denote
denotes
described
describes
design
designed
dest
destLen,
dest[*destLen]
dest[0 .. *destLen-1]
destination
detail,
details
detect
detected
detected.
determine
determined
different
difficult
difficulties
difficulties,
directory
disk
distribution,
document
documentation
does
doesn't
doing
don't
done
during
easily
easy
effort
either
else
embedded
encounter
encouraged
end
end-of-stream
end-to-end.
enough
enough,
enough.
ensure
entirely
entirety
environment.
errno
error
error,
error.
errors
errors,
especially
eventually
every
example,
exceeds
except
existing
expansion
expense
facilitate
facility
facts
failure
family
faster
fclose
ferror(f)
fflush
fields
file
file,
file.
filenames
files
files,
files.
find
first
flag
flags
flexible
following
for
forces
format
four
free
from
function
function.
functions
functions.
general
generally
get
getting
give
given
gives
giving
global
good
guarantee
handle
handle,
handled
handling
hard
has
have
haven't
header
help
helpful
high-level
holding
how
http://www.
hundred
ideas.
if 
if (!f) {
if (bzerror != BZ_OK) {
if (bzerror == BZ_IO_ERROR) {
if insufficient memory is available
if the
if the size of the compressed data exceeds
ignored
immediately
important
including
inclusive.
indicate
indicating how much output space is available. 
indicator
inefficient.
information
initialisation
initialised
initialised,
input
input.
insufficient
int
int          
int     bzerror;
int     nBuf;
int     nWritten;
int workFactor );
int*
integrity
intended
interest
interface
interface,
interface.
interfaces
internal
into
into the destination buffer,
inverse
is 
is nonzero
is returned.
is returned.  If the compressed data won't fit,
is unchanged, and
isn't
issues
its
itself
jseward@acm.org
jseward@acm.org.
just
kbytes
kbytes.
large
larger
len
len < 0
length
less
level
libbzip2
library
library,
library.
like
limit,
list
little
logical
long
look
low-level
machine
machine,
made
magic
maintains
make
makes
making
malloc
manner
manual
many
maximum
may
meaning
means
mechanism
mechanism,
megabytes
megabytes.
memory
memory,
memory-to-memory
memory.
might
misses.
mode
more
much
must
nUnused
nWritten;
name
names
nbytes_out
need
needed
needless
never
new
next
next_in
next_out
nonzero
normal
normal.
not
nothing
number
occur.
on-the-fly
once
one
only
opaque
opaque,
open
opened
operating
operation
operations
option
options
or 
original
original.
other
otherwise
otherwise.
output
output,
output.
overflow.
overwrite
own
parameter
parameters
part
pass
passed
passes
passing
people
performance
perhaps
perror
pertaining
placed
placed,
platforms.
please,
point
point,
pointer
portability
possible
possible,
preprocessor
present
pretty
previous
probably
problem
problem.
problems
problems,
problems.
process
processed.
produce
program
program,
program.
programming
project
properly
provide
provided
provided.
provides
pseudo-random
public
purposes.
randomisation
randomisation.
range
ratio
read
read.
reading
real
really
record
recorded
records
recover
reflect
regarded
release
relevant
remaining
remove
repeated
repeatedly
repetitive
repetitive,
report
report.
represent
request
requested
require
required
required,
research
resorting
resources
respectively.
result
resulting
return
return,
returned
returned.
returns
right
routines
runs
same
searching
segmentation
send
sequence
set
set.
settings
several
should
should indicate how many bytes the library may read. 
should point
signalled
similar
simple
simpler
since
single
situation
size
size.
sizes
slowly
small
small,
small-mode
smaller
software
software.
some
something
sometimes
sorting
source
source,
sourceLen,
sourceLen-1]
source[0 .. sourceLen-1]
space
special
specific
specified
specify
speed
speed.
standard
start
starting
state
state,
state.
stdio
stdout.
still
stored
straight
stream
stream's
stream,
stream.
streams
strictly
strm
strm->s
structure
structures
subsequent
successfully,
successfully.
suffix
summary
supplied
supply
supported,
sure
symbol
take
takes
terribly
test
testing
testing.
tests
text
than
that
the
them
them.
then
there
these
they
this
this,
those
though
thread-safe.
three
through
time
time,
to 
to reflect the number of bytes it has read.
to reflect the number of bytes output.
to transfer data between them.
total
total_in
total_out
transfer
transform
tried
try
tsuneo-y@is.aist-nara.ac.jp
unchanged,
uncompressed
underlying
understood
undetected
unsigned int  sourceLen,
unsigned int* destLen,
until
unused
updates
upon
usage
use
used
used.
useful
user-supplied
uses
using
usually
value
values
values.
values:
variables
variations
various
verbosity
verbosity,
version
version,
versions
very
void
volume
want
was
was opened with
was returned
well
were
what
whatever
when
which
whilst
will
will not write data at or beyond
with
with action =
without
won't
work
workFactor
worst
worst-case
would
write
writes
writing
writing,
written
you
you'd
you'll
your
