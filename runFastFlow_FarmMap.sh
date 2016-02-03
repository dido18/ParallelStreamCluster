#!/bin/bash


#create the folder if doesn't exist
mkdir -p run


# check if there are two inputs


if [ $# -lt 2 ];
   then
   echo "Usage:  $0  [test | simsmall | simmedium | simlarge | simdev |stream]  NThreads"
   exit 1
fi

NTHREADS=$2;
BINARY_PATH="./bin/ff_stream_cluster_FarmMap"

case $1 in
    test)
        echo "Run $1 with ${NTHREADS} threads. "
        ${BINARY_PATH}  2 5 1 10 10 5 none run/ff_output.txt ${NTHREADS}
        ;;
    simsmall)
        echo "Running $1  with ${NTHREADS} threads"
       ${BINARY_PATH} 10 20 32 4096 4096 1000 none run/ff_output.txt ${NTHREADS}
        ;;
    simmedium)
        echo "Running $1  with ${NTHREADS} threads"
        ${BINARY_PATH} 10 20 64 8192 8192 1000 none run/ff_output.txt ${NTHREADS}
        ;;
    simlarge)
        echo "Running $1  with ${NTHREADS} threads"
        ${BINARY_PATH} 10 20 128 16384 16384 1000 none run/ff_output.txt ${NTHREADS}
            ;;
    simdev)
        echo "Running $1  with ${NTHREADS} threads "
        ${BINARY_PATH}  3 10 3 16 16 10 none run/ff_output.txt ${NTHREADS}
        ;;
    stream)
        echo "Running $1 with $2 threads ...."
         ${BINARY_PATH}  3 10 3 64 16 20 none run/omp_output.txt ${NTHREADS}
        ;;
    *)
        echo "Usage:  $0  [test | simsmall | simmedium | simlarge | simdev | stream] Nthreads"
            echo "       'make install' if binary file are not present"
esac
