//
// Created by dido-ubuntu on 09/02/16.
//

#ifndef PARALLELSTREAMCLUSTER_SIMSTREAM_H
#define PARALLELSTREAMCLUSTER_SIMSTREAM_H

#include <climits>
#include "Points.h"

class SimStream: public PStream {
    //synthetic stream
public:
    SimStream(long n_ ) {
        srand48(1);
        n = n_;
    }
    size_t read( float* dest, int dim, int num ) {
        size_t count = 0;
        for( int i = 0; i < num && n > 0; i++ ) {
            for( int k = 0; k < dim; k++ ) {
                dest[i*dim + k] = lrand48()/(float)INT_MAX;
            }
            n--;
            count++;
        }
        return count;
    }


    int ferror() {
        return 0;
    }
    int feof() {
        return n <= 0;
    }
    ~SimStream() {
    }
private:
    long n;
};


#endif //PARALLELSTREAMCLUSTER_SIMSTREAM_H
