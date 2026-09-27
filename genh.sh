#!/bin/sh

cat src/dictator.c | awk '
/^struct/ {
	split($0, aa, " ");
	print "typedef struct "aa[2]" "aa[2]";"
}
/^union/ {
	split($0, aa, " ");
	print "typedef union "aa[2]" "aa[2]";"
}
/^func/ {
	sub("^func ", "", $0);
	sub(" *{ *", ";", $0);
	print $0
}' > src/dictator.h
