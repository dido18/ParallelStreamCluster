//
// Created by dido-ubuntu on 10/02/16.
//

#ifndef PARALLELSTREAMCLUSTER_HELPER_H
#define PARALLELSTREAMCLUSTER_HELPER_H

#include "Points.h"
#include <sys/time.h>

// header
namespace helper
{
    //static long start(unique_ptr<Points> p, float kMin, float kMax, int dim, long centersize){
    /*static long start(Points * p, float kMin, float kMax, int dim, long centersize){
        long* kfinal;
        StreamClusterEntry(p, kMin, kMax, dim, centersize, kfinal);
        return *kfinal;
    }*/


    static double gettime() {
        struct timeval t;
        gettimeofday(&t, NULL);
        return (double) t.tv_sec + t.tv_usec * 1e-6;
    }

}

#endif //PARALLELSTREAMCLUSTER_HELPER_H
