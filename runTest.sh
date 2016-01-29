#!/bin/bash


#create the folder if doesn't exist
mkdir -p run


NTHREADS=1

case $1 in
    test)
        echo "Run simple test..."
        ./bin/ff_stream_cluster  2 5 1 10 10 5 none run/ff_output.txt ${NTHREADS}
        ;;
    simsmall)
        echo 'Running simsmall test ...?'
        ./bin/ff_stream_cluster 10 20 32 4096 4096 1000 none run/ff_output.txt ${NTHREADS}
        ;;
    simmedium)
        echo 'Running simmedium test ...'
        ./bin/ff_stream_cluster 10 20 64 8192 8192 1000 none run/ff_output.txt ${NTHREADS}
        ;;
    simlarge)
            echo $'Running simlarge test...'
        ./bin/ff_stream_cluster 10 20 128 16384 16384 1000 none run/ff_output.txt ${NTHREADS}
            ;;
    simdev)
        echo 'Running simdev test ...'
        ./bin/ff_stream_cluster  3 10 3 16 16 10 none run/ff_output.txt ${NTHREADS}
        ;;
    *)
        echo "Usage:  $0  [test | simsmall | simmedium | simlarge | simdev]"
            echo "       'make install' if binary file are not present"
esac
