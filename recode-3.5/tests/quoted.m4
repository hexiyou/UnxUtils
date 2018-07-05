#							-*- shell-script -*-

AT_SETUP(block of lines from Quoted Printable)
dnl      ------------------------------------

AT_CHECK(
[recode qp..x1 < $at_srcdir/quoted-data
], 0,
[0x44, 0x65, 0x61, 0x72, 0x20, 0xDE, 0x6F, 0x72, 0x76, 0x61, 0x72, 0x64,
0xF0, 0x75, 0x72, 0x2C, 0x0A, 0x0A, 0xAB, 0x20, 0x4F, 0xF9, 0x20, 0x71,
0x75, 0x27, 0x69, 0x6C, 0x20, 0x72, 0xE9, 0x73, 0x69, 0x64, 0x65, 0x2C,
0x20, 0xE0, 0x20, 0x4E, 0xEE, 0x6D, 0x65, 0x73, 0x20, 0x6F, 0x75, 0x20,
0x6D, 0xEA, 0x6D, 0x65, 0x20, 0x43, 0x61, 0x70, 0x68, 0x61, 0x72, 0x6E,
0x61, 0xFC, 0x6D, 0x2C, 0x20, 0x74, 0x6F, 0x75, 0x74, 0x20, 0x46, 0x72,
0x61, 0x6E, 0xE7, 0x61, 0x69, 0x73, 0x20, 0x69, 0x6E, 0x73, 0x63, 0x72,
0x69, 0x74, 0x0A, 0x61, 0x75, 0x20, 0x72, 0xF4, 0x6C, 0x65, 0x20, 0x70,
0x61, 0x79, 0x65, 0x72, 0x61, 0x20, 0x73, 0x6F, 0x6E, 0x20, 0x64, 0xFB,
0x20, 0x64, 0xE8, 0x73, 0x20, 0x61, 0x76, 0x61, 0x6E, 0x74, 0x20, 0x4E,
0x6F, 0xEB, 0x6C, 0x2C, 0x20, 0x71, 0x75, 0x27, 0x69, 0x6C, 0x20, 0x73,
0x6F, 0x69, 0x74, 0x20, 0x6E, 0x61, 0xEF, 0x66, 0x20, 0x6F, 0x75, 0x20,
0x72, 0xE2, 0x6C, 0x65, 0x75, 0x72, 0x2E, 0x20, 0xBB, 0x0A, 0x49, 0x6E,
0x63, 0x6F, 0x6D, 0x70, 0x6C, 0x65, 0x74, 0x65, 0x20, 0x6C, 0x61, 0x73,
0x74, 0x20, 0x6C, 0x69, 0x6E, 0x65
])

AT_CLEANUP()

AT_SETUP(block of lines from Quoted Printable and back)
dnl      ---------------------------------------------

AT_CHECK(
[set -e
cp $at_srcdir/quoted-data output
chmod +w output
recode qp..x1 output
recode x1..qp output
diff $at_srcdir/quoted-data output
set +e
])

AT_CLEANUP(output)
