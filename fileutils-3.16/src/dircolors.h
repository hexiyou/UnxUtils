#define G_N_LINES 76

const size_t G_line_length[G_N_LINES] =
{
  65, 72, 0, 59, 61, 0, 77, 10, 12, 14, 14, 14, 14, 13, 13, 13, 13, 13, 13,
  10, 10, 0, 73, 64, 18, 64, 19, 72, 25, 72, 68, 22, 22, 27, 17, 19, 34,
  39, 45, 0, 44, 10, 0, 70, 75, 48, 0, 73, 40, 11, 11, 11, 11, 0, 48,
  10, 10, 10, 10, 10, 10, 10, 10, 10, 26, 10, 10, 10, 10, 10, 10, 10, 10,
  10, 9, 9
};

const char *const G_line[G_N_LINES] =
{
  "# Configuration file for dircolors, a utility to help you set the",
  "# LS_COLORS environment variable used by GNU ls with the --color option.",
  "",
  "# The keywords COLOR, OPTIONS, and EIGHTBIT (honored by the",
  "# slackware version of dircolors) are recognized but ignored.",
  "",
  "# Below, there should be one TERM entry for each termtype that is colorizable",
  "TERM linux",
  "TERM console",
  "TERM con132x25",
  "TERM con132x30",
  "TERM con132x43",
  "TERM con132x60",
  "TERM con80x25",
  "TERM con80x28",
  "TERM con80x30",
  "TERM con80x43",
  "TERM con80x50",
  "TERM con80x60",
  "TERM xterm",
  "TERM vt100",
  "",
  "# Below are the color init strings for the basic file types. A color init",
  "# string consists of one or more of the following numeric codes:",
  "# Attribute codes:",
  "# 00=none 01=bold 04=underscore 05=blink 07=reverse 08=concealed",
  "# Text color codes:",
  "# 30=black 31=red 32=green 33=yellow 34=blue 35=magenta 36=cyan 37=white",
  "# Background color codes:",
  "# 40=black 41=red 42=green 43=yellow 44=blue 45=magenta 46=cyan 47=white",
  "NORMAL 00	# global default, although everything should be something.",
  "FILE 00 	# normal file",
  "DIR 01;34 	# directory",
  "LINK 01;36 	# symbolic link",
  "FIFO 40;33	# pipe",
  "SOCK 01;35	# socket",
  "BLK 40;33;01	# block device driver",
  "CHR 40;33;01 	# character device driver",
  "ORPHAN 40;31;01 # symlink to nonexistent file",
  "",
  "# This is for files with execute permission:",
  "EXEC 01;32",
  "",
  "# List any file extensions like '.gz' or '.tar' that you would like ls",
  "# to colorize below. Put the extension, a space, and the color init string.",
  "# (and any comments you want to add after a '#')",
  "",
  "# If you use DOS-style suffixes, you may want to uncomment the following:",
  "#.cmd 01;32 # executables (bright green)",
  "#.exe 01;32",
  "#.com 01;32",
  "#.btm 01;32",
  "#.bat 01;32",
  "",
  ".tar 01;31 # archives or compressed (bright red)",
  ".tgz 01;31",
  ".arj 01;31",
  ".taz 01;31",
  ".lzh 01;31",
  ".zip 01;31",
  ".z   01;31",
  ".Z   01;31",
  ".gz  01;31",
  ".deb 01;31",
  ".jpg 01;35 # image formats",
  ".gif 01;35",
  ".bmp 01;35",
  ".ppm 01;35",
  ".tga 01;35",
  ".xbm 01;35",
  ".xpm 01;35",
  ".tif 01;35",
  ".mpg 01;37",
  ".avi 01;37",
  ".gl 01;37",
  ".dl 01;37"
};
