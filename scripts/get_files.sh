#! /bin/bash

# The number in the part (NR % 3 == 0) decides how many files will be in one line
ls src | grep .c | awk '{printf "%s ", $0; if (NR % 1 == 0) print "\\"}' > files_sorted