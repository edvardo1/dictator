#!/bin/sh

expect() {
		./dictator \
			-r "examples/$1" \
			-t "examples/$2" > test_file.txt && \
		if cmp test_file.txt examples/expected-portuguese-from-latin.txt; then
			echo "[OK]    latin to portuguese test"
		else
			echo "[ERROR] latin to portuguese test"
		fi
		if test -e test_file.txt; then
			rm test_file.txt
		fi
}

if ./build.sh; then :; else
	echo "build failed"
	exit 1
fi

expect latin-to-portuguese.dictator portuguese.txt
