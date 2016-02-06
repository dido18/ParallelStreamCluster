#!/bin/bash

mkdir -p run


# check if there are two inputs
if [ $# -lt 2 ];
   then
   echo "Usage:  $0  [test | simsmall | simmedium | simlarge | simdev]  NThreads"
   exit 1
fi


NTHREADS=$2;


case $1 in
    test)
        echo "Run simple test..."
        bin/streamcluster 2 5 1 10 10 5 none run/parsec_output.txt ${NTHREADS}
        ;;
    simsmall)
        echo 'Running simsmall test ...?'
        bin/streamcluster 10 20 32 4096 4096 1000 none run/parsec_output.txt ${NTHREADS}
        ;;
    simmedium)
        echo 'Running simmedium test ...'
        bin/streamcluster 10 20 64 8192 8192 1000 none run/parsec_output.txt ${NTHREADS}
        ;;
    simlarge)
        echo $'Running simlarge test...'
        bin/streamcluster 10 20 128 16384 16384 1000 none run/parsec_output.txt ${NTHREADS}
        ;;
    simdev)
        echo 'Running simdev test ...'
        bin/streamcluster 3 10 3 16 16 10 none run/parsec_output.txt ${NTHREADS}
        ;;
    *)
        echo "Usage:  $0 [test | simsmall | simmedium | simlarge | simdev] NThreads"
        echo "       'make install' if binary file are not present"
esac
