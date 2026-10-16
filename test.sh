#!/bin/sh

cmd() {
	echo "$@" 1>&2
	$@
}

expect() {
	cmd ./dictator \
		-r "examples/$2" \
		-t "examples/$3" > test_file.txt && \
	if cmp test_file.txt "examples/$4"; then
		echo "[OK]    \"$1\" test"
	else
		echo "[ERROR] \"$1\" test"
	fi
	if test -e test_file.txt; then
		rm test_file.txt
	fi
}

if ./build.sh; then :; else
	echo "build failed"
	exit 1
fi

echo testing...
expect "latin to portuguese" latin-to-portuguese.dictator portuguese.txt expected-portuguese-from-latin.txt
expect "list" test-list.dictator test-list.txt expected-test-list.txt
