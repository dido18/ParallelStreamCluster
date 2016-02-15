#!/bin/bash

# runTest [ffMap,ffFarmMap, parsec, rodinia] [test, simsmall, simlarge, native] noThreads
#
mkdir -p run

USAGE="usage: $0 [ffmap | fffarmmap | parsec | rodinia] [test| simsmall| simlarge| native] [farmWorkers pfWorkers | noThreas] nTimes "

if [ $# -lt 4 ];
   then
   echo ${USAGE}
   exit 1
fi


OUTPUT_PATH="run/$1.$2.output"

source "conf/$1.bin"   #load the binary path from the file in the  conf/ folder
BINARY_PATH=$run_exec  #run_exec contains the path of the binary file of the first argument


source "conf/$2.runconf"
RUN_ARGS=$run_args    #run_args contains the arguments for the programm


case "$1" in
        "ffmap" |  "fffarmmap")
        	echo "Running ${1} test of ${BINARY_PATH} with ${3} farmWorker and ${4} mapWorkers ${5} times..."
		     for i in `seq 1 $5`;
		     do
		           ${BINARY_PATH} ${RUN_ARGS} ${OUTPUT_PATH} ${3}  ${4}
             done

            ;;
        "ffmap")
            echo "Running ${1} test of ${BINARY_PATH} with ${3}  mapWorkers ${4} times..."
        	for i in `seq 1 $5`;
        	    do
        	          ${BINARY_PATH} ${RUN_ARGS} ${OUTPUT_PATH} ${3}  ${4}
               done
        ;;
        "parsec" | "rodinia")
		echo "Running ${1} test of ${BINARY_PATH} with ${3} threads ${4} times ..."
		 for i in `seq 1 $5`;
        	do
        	   ${BINARY_PATH} ${RUN_ARGS} ${OUTPUT_PATH} ${4}    # run rodinia or parsec with nthreads
            done

            ;;
        *)
            echo ${USAGE}
            exit 1
 
esac

