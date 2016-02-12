//
// Created by dido-ubuntu on 12/02/16.
//

#ifndef PARALLELSTREAMCLUSTER_COLLECTOR_H
#define PARALLELSTREAMCLUSTER_COLLECTOR_H


#include <ff/node.hpp>
#include "Points.h"
#include "UtilClusters.h"

using namespace ff;

class Collector: public ff_minode_t<Points> {
public:
    long clustersize;
    Points * finalCenters;
    float* centerBlock ;

    Collector(long clustersz, int dim, long kmin, long kmax, int pf_workers):
            clustersize{clustersz}, finalCenters(new Points(dim, clustersz)), sc(pf_workers, kmin, kmax){

            centerBlock = (float*)malloc(clustersize*dim*sizeof(float));

             for (int i = 0; i < clustersz; i++) {
                (finalCenters->p[i]).coord = &centerBlock[i * dim];// points contains pointer to the block array containting the coordinates
                 finalCenters->p[i].weight = 1.0;
             }

    };

    Points * svc(Points *);
    void svc_end();
private :
    UtilClusters sc;




};


#endif //PARALLELSTREAMCLUSTER_COLLECTOR_H
