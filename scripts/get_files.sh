#! /bin/bash

ls src | grep .c | awk '{printf "%s ", $0; if (NR % 1 == 0) print "\\"}' > files_sorted