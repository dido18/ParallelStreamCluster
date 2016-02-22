#!/bin/bash
#--------------------------------------
# scMngmt.sh
#     Reads in the conf/ directory the binary path and the parameters.
#     Runs the specific parallel version (ff_map or ff_farm) with an input type.
#
#----------------------------------------
mkdir -p run

USAGE="Runs the parallel versions on the host/local machine
     \n usage:  \n\t$0 [ff_map | ff_farm] [ simmedum | simlarge | native] nWorkers nTimes "

#check the number of input of the script
if [ $# -lt 4 ];
   then
   echo -e ${USAGE}
   exit 1
fi


OUTPUT_PATH="./run/$1.$2.out"   #is utilized for the output and for the times results.

source "conf/$1.bin"   #load the binary path from the file in the  conf/ folder
BINARY_PATH=$run_exec  #run_exec contains the path of the binary file of the first argument

source "conf/$2.runconf"
RUN_ARGS=$run_args    #run_args contains the arguments for the programm

case "$1" in
        "ff_farm")
        	echo "Running ${1} of ${BINARY_PATH} ${RUN_ARGS} with ${3} farmWorker ${4} times..."
		    for i in `seq 1 $5`;
		    do
		          ${BINARY_PATH} ${RUN_ARGS} ${OUTPUT_PATH} ${3}
            done

            ;;
        "ff_map")
            echo "Running ${1} test of ${BINARY_PATH} ${RUN_ARGS}  with ${3} mapWorkers ${4} times..."
        	for i in `seq 1 $4`;
        	    do
        	          ${BINARY_PATH} ${RUN_ARGS} ${OUTPUT_PATH} ${3}
               done
        ;;
        *)
         echo -e ${USAGE}
         exit 1
esac


