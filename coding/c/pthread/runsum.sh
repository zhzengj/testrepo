#!/bin/bash

if [ -f 'a.out' ] ; then
	rm a.out
fi

CFLAGS='-Wall'
LFALGS='-lpthread'

gcc ${CFLAGS} sum.c ${LFALGS}

echo "1 yi"
time ./a.out -s 1 -e 100000000
echo '1 thread'
time ./a.out -s 1 -e 100000000 -t 1
echo '2 thead'
time ./a.out -s 1 -e 100000000 -t 2
echo '3 thread'
time ./a.out -s 1 -e 100000000 -t 3

echo 
echo "10 yi"
time ./a.out -s 1 -e 1000000000
echo '1 thread'
time ./a.out -s 1 -e 1000000000 -t 1
echo '2 thread'
time ./a.out -s 1 -e 1000000000 -t 2
echo '3 thread'
time ./a.out -s 1 -e 1000000000 -t 3

echo 
echo "20 yi"
time ./a.out -s 1 -e 2000000000
echo '1 thread'
time ./a.out -s 1 -e 2000000000 -t 1
echo '2 thread'
time ./a.out -s 1 -e 2000000000 -t 2
echo '3 thread'
time ./a.out -s 1 -e 2000000000 -t 3

