//
// Created by dido-ubuntu on 09/02/16.
//

#ifndef PARALLELSTREAMCLUSTER_EMITTER_H
#define PARALLELSTREAMCLUSTER_EMITTER_H

#include <ff/node.hpp>
#include "Points.h"
#include "PStream.h"
#include "UtilClusters.h"


using  namespace ff;

class Emitter: public ff_node_t<Points,Points> {

public:
    PStream * stream;
    long chunksize;
    int dim;
    long IDoffset = 0;   // Count the points read from the stream.

    Emitter (PStream * Stream, long cksize, long d);

    Points *svc (Points *);

    int run_and_wait_end(bool=false);


};


#endif //PARALLELSTREAMCLUSTER_EMITTER_H
