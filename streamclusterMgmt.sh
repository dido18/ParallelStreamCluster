#!/bin/bash

# runTest [ffMap,ffFarmMap, parsec, rodinia] [test, simsmall, simlarge, native] noThreads
#
mkdir -p run

USAGE="usage: $0 [ffmap, fffarmmap, parsec, rodinia] [test, simsmall, simlarge, native] noThreads"

if [ $# -lt 3 ];
   then
   echo ${USAGE}
   exit 1
fi

OUTPUT_PATH="run/$1.$2.output"

source "conf/$1.bin"
BINARY_PATH=$run_exec


source "conf/$2.runconf"
RUN_ARGS=$run_args

NTHREADS=$3

echo "Running ${1} test of ${BINARY_PATH} with ${NTHREADS} threads ..."

${BINARY_PATH} ${RUN_ARGS} ${OUTPUT_PATH} ${NTHREADS}
