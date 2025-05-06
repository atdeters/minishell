#! /bin/bash

# Variables
SRC='src'			# directory with your files you want to sort
FPL='1'				# number of files per line
OUT='files_sorted'	# filename for the output of the sorted files

# Script
ls $SRC | grep .c | awk -v n=$FPL '{printf "%s ", $0; if (NR % n == 0) print "\\"}' > $OUT