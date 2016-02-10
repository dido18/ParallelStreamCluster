//
// Created by dido-ubuntu on 10/02/16.
//

#ifndef PARALLELSTREAMCLUSTER_HELPERSTREAMCLUSTER_H
#define PARALLELSTREAMCLUSTER_HELPERSTREAMCLUSTER_H


//#include "StreamCluster++.h"

class HelperStreamCluster{
public:

  //static long start(unique_ptr<Points> p, float kMin, float kMax, int dim, long centersize){
  static long start(Points * p, float kMin, float kMax, int dim, long centersize){
    long* kfinal;
      StreamClusterEntry(p, kMin, kMax, dim, centersize, kfinal);
    return *kfinal;
  }

};

#endif //PARALLELSTREAMCLUSTER_HELPERSTREAMCLUSTER_H



