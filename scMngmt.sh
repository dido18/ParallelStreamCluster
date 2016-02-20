#!/bin/bash
#--------------------------------------
# scMngmt.sh  run binary with an input different times.
#
#----------------------------------------
mkdir -p run

USAGE="usage: $0 [ff_map | ff_farm | rodinia] [simsmall | simmedum | simlarge | native] nWorkers nTimes "

#check the number of input of the script
if [ $# -lt 4 ];
   then
   echo ${USAGE}
   exit 1
fi


OUTPUT_PATH="./run/$1.$2.out"           #is utilized for the output and for the times results (appends _tests in the main)

source "conf/$1.bin"   #load the binary path from the file in the  conf/ folder
BINARY_PATH=$run_exec  #run_exec contains the path of the binary file of the first argument

source "conf/$2.runconf"
RUN_ARGS=$run_args    #run_args contains the arguments for the programm

case "$1" in
        "ff_farm")
        	echo "Running ${1} of ${BINARY_PATH} ${RUN_ARGS} with ${3} farmWorker ${4} times..."
		    for i in `seq 1 $5`;
		    do
		          ${BINARY_PATH} ${RUN_ARGS} ${OUTPUT_PATH} ${3} 1
            done

            ;;
        "ff_map")
            echo "Running ${1} test of ${BINARY_PATH} ${RUN_ARGS}  with ${3} mapWorkers ${4} times..."
        	for i in `seq 1 $4`;
        	    do
        	          ${BINARY_PATH} ${RUN_ARGS} ${OUTPUT_PATH} 1  ${3}
               done
        ;;
        "parsec" | "rodinia")
		echo "Running ${1} test of ${BINARY_PATH} ${RUN_ARGS} with ${3} threads ${4} times ..."
		 for i in `seq 1 $5`;
        	do
        	   ${BINARY_PATH} ${RUN_ARGS} ${OUTPUT_PATH} ${3}    # run rodinia or parsec with nthreads
            done
            ;;
        *)
         echo ${USAGE}
         exit 1
esac


