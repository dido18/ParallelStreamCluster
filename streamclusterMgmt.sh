#!/bin/bash

# runTest [ffMap,ffFarmMap, parsec, rodinia] [test, simsmall, simlarge, native] [farmWorkers pfWorkers | noThreas]  noThreads Ntimes
#
mkdir -p run


USAGE="usage: $0 [ffmap | fffarmmap | parsec | rodinia] [test| simsmall| simlarge| native] [farmWorkers pfWorkers | noThreas] nTimes "


OUTPUT_PATH="./run/$1.$2.output"           #is utilized for the output and for the times results (appends _tests in the main)
OUTPUT_PATH_TIMES="${OUTPUT_PATH}_times" # same name used in the main.cpp for storing only the execution times

LATEX_DATA="./report/report_latex/graphix/$1.$2.csv"

#check the number of input of the script
if [ $# -lt 4 ];
   then
   echo ${USAGE}
   exit 1
fi


# romove the file storing the execution times and output results.
echo "removed $OUTPUT_PATH_TIMES"
rm -f "$OUTPUT_PATH_TIMES"


source "conf/$1.bin"   #load the binary path from the file in the  conf/ folder
BINARY_PATH=$run_exec  #run_exec contains the path of the binary file of the first argument


source "conf/$2.runconf"
RUN_ARGS=$run_args    #run_args contains the arguments for the programm

N_DEGREE=0    # parallelism degree used

case "$1" in
        "fffarmmap")
        	echo "Running ${1} of ${BINARY_PATH} with ${3} farmWorker and ${4} mapWorkers ${5} times..."
        	N_DEGREE=$(($3+$4))
		     for i in `seq 1 $5`;
		     do
		           ${BINARY_PATH} ${RUN_ARGS} ${OUTPUT_PATH} ${3} ${4}
             done

            ;;
        "ffmap")
            echo "Running ${1} test of ${BINARY_PATH} with ${3}  mapWorkers ${4} times..."
            N_DEGREE=$3
        	for i in `seq 1 $4`;
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

#execute perl script that compute the average time of the execution
#read AVERAGE <<<$(./average_time.pl $OUTPUT_PATH_TIMES)
#echo "Perl script executes the average times: $AVERAGE "

#echo "$N_DEGREE,$AVERAGE" >> $LATEX_DATA
#echo "Writes ($N_DEGREE, $AVERAGE) in $LATEX_DATA"


