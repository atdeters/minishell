#! /bin/bash

ls src | grep .c | awk '{print $0 " \\"}' > files_sorted