//
// Created by dido-ubuntu on 09/02/16.
//

#ifndef PARALLELSTREAMCLUSTER_WORKER_H
#define PARALLELSTREAMCLUSTER_WORKER_H

#include <ff/barrier.hpp>
#include <ff/node.hpp>

#include "Points.h"
#include "UtilClusters.h"

using namespace std;
using namespace ff;

class Worker: public ff_node_t<Points> {

public:
    int dim;
    long kmin;
    long kmax;
    long centersize;
    UtilClusters sc;


    Worker(int d, long kMIN, long kMAX, long centersz, long pf_workers);

    Points * svc(Points * p);


};


#endif //PARALLELSTREAMCLUSTER_WORKER_H
