#!/bin/bash

mkdir -p run



#bin/sc_omp 2 5 1 10 10 5 none run/output.rodinia.omp 1
# check if there are two inputs
#
USAGE=" Usage:  $0  [test | simsmall | simmedium | simlarge | simdev | native] noThreads
      \n make install' if binary file are not present"

if [ $# -lt 2 ];
   then
   echo -e ${USAGE}
   exit 1
fi

NTHREADS=$2
PATH_BIN=bin/sc_omp

case $1 in
    test)
        echo "Running $1 with $2 threads ...."
        ${PATH_BIN}  2 5 1 10 10 5 none run/omp_output.txt ${NTHREADS}
        ;;
    simsmall)
       echo "Running $1 with $2 threads ...."
        ${PATH_BIN} 10 20 32 4096 4096 1000 none run/omp_output.txt ${NTHREADS}
        ;;
    simmedium)
       echo "Running $1 with $2 threads ...."
        bin/sc_omp 10 20 64 8192 8192 1000 none run/omp_output.txt ${NTHREADS}
        ;;
    simlarge)
         echo "Running $1 with $2 threads ...."
        ${PATH_BIN}  10 20 128 16384 16384 1000 none run/omp_output.txt ${NTHREADS}
            ;;
    simdev)
         echo "Running $1 with $2 threads ...."
        ${PATH_BIN}  3 10 3 16 16 10 none run/omp_output.txt ${NTHREADS}
        ;;
   native)
      echo "Running $1 with $2 threads ...."
         ${BINARY_PATH} 10 20 128 1000000 200000 5000 none ${OUTPUT_PATH} ${NTHREADS}
      ;;
   *)
    echo -e ${USAGE}
esac

#stream)
#   echo "Running $1 with $2 threads ...."
#   ${PATH_BIN}  3 10 3 64 16 20 none run/omp_output.txt ${NTHREADS}
#   ;;
