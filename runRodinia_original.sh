#!/bin/bash

mkdir -p run

USAGE=" Usage:  $0  [test | simsmall | simmedium | simlarge | simdev | native ] noThreads
      \n make install' if binary file are not present"


NTHREADS=1

if [ $# -lt 2 ];
   then
      echo -e ${USAGE}
   exit 1
fi

NTHREADS=$2

BINPATH=./bin/sc_original
OUTPUT=run/original.output

case $1 in
    test)
        echo "Running $1 with ${NTHREADS} threads"
        ${BINPATH} 2 5 1 10 10 5 none ${OUTPUT} ${NTHREADS}
        ;;
    simsmall)
        echo "Running $1 with ${NTHREADS} threads"
        ${BINPATH} 10 20 32 4096 4096 1000 none ${OUTPUT} ${NTHREADS}
        ;;
    simmedium)
        echo "Running $1 with ${NTHREADS} threads"
        ${BINPATH} 10 20 64 8192 8192 1000 none ${OUTPUT} ${NTHREADS}
        ;;
    simlarge)
        echo "Running $1 with ${NTHREADS} threads"
        ${BINPATH} 10 20 128 16384 16384 1000 none ${OUTPUT} ${NTHREADS}
            ;;
    simdev)
        echo "Running $1 with ${NTHREADS} threads"
        ${BINPATH}  3 10 3 16 16 10 none ${OUTPUT} ${NTHREADS}
        ;;
   native)
         echo "Running $1 with $2 threads ...."
         ${BINPATH}  10 20 128 1000000 200000 5000 none ${OUTPUT_PATH} ${NTHREADS}
         ;;
    *)
        echo -e ${USAGE}
esac
