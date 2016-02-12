//
// Created by dido-ubuntu on 09/02/16.
//



#ifndef PARALLELSTREAMCLUSTER_STREAM_H
#define PARALLELSTREAMCLUSTER_STREAM_H

#include <glob.h>
#include "Points.h"
class PStream {
public:
    virtual size_t read( float* dest, int dim, int num ) = 0;
    virtual int ferror() = 0;
    virtual int feof() = 0;
    virtual ~PStream() {
    }
};



#endif //PARALLELSTREAMCLUSTER_STREAM_H
