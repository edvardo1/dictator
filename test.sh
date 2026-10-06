#!/bin/sh

if ./build.sh; then
	./dictator \
		-r examples/latin-to-portuguese.dictator \
		-t examples/portuguese.txt > test_file.txt && \
	if cmp a b; then
		echo "[OK]    latin to portuguese test"
	else
		echo "[ERROR] latin to portuguese test"
	fi
else
	echo "build failed"
fi
