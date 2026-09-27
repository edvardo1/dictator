#!/bin/sh

#set -o
./genh.sh
cc -I./include -Wall -Werror -Wextra -Og -ggdb -o dictator src/dictator.c
