#!/bin/bash


#create the folder if doesn't exist
mkdir -p run


# check if there are two inputs
#
USAGE=" Usage:  $0  [test | simsmall | simmedium | simlarge | simdev | native] noThreads
      \n make install' if binary file are not present"

if [ $# -lt 2 ];
   then
   echo -e ${USAGE}
   exit 1
fi

NTHREADS=$2;
BINARY_PATH="./bin/ff_stream_cluster_noFarm"
OUTPUT_PATH="./run/ff_noFarm_output.txt"

case $1 in
    test)
        echo "Run $1 with ${NTHREADS} threads. "
        ${BINARY_PATH}  2 5 1 10 10 5 none ${OUTPUT_PATH} ${NTHREADS}
        ;;
    simsmall)
        echo "Running $1  with ${NTHREADS} threads"
       ${BINARY_PATH} 10 20 32 4096 4096 1000 none ${OUTPUT_PATH} ${NTHREADS}
        ;;
    simmedium)
        echo "Running $1  with ${NTHREADS} threads"
        ${BINARY_PATH} 10 20 64 8192 8192 1000 none ${OUTPUT_PATH} ${NTHREADS}
        ;;
    simlarge)
        echo "Running $1  with ${NTHREADS} threads"
        ${BINARY_PATH} 10 20 128 16384 16384 1000 none ${OUTPUT_PATH} ${NTHREADS}
            ;;
    simdev)
        echo "Running $1  with ${NTHREADS} threads "
        ${BINARY_PATH}  3 10 3 16 16 10 none ${OUTPUT_PATH} ${NTHREADS}
        ;;
    native)
        echo "Running $1 with $2 threads ...."
         ${BINARY_PATH} 10 20 128 1000000 200000 5000 none ${OUTPUT_PATH} ${NTHREADS}
          ;;
    *)
        echo -e ${USAGE}
esac
