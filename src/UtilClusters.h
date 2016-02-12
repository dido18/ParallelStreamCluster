//
// Created by dido-ubuntu on 10/02/16.
//

#ifndef PARALLELSTREAMCLUSTER_STREAMCLUSTER_H
#define PARALLELSTREAMCLUSTER_STREAMCLUSTER_H

#include "Points.h"
#include "ff/parallel_for.hpp"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <sys/resource.h>
#include <limits.h>
#include <omp.h>

using namespace std;
using namespace ff;

struct pkmedian_arg_t {
    Points *points;
    long kmin;
    long kmax;
    long *kfinal;
    int pid;
    pthread_barrier_t *barrier;
};

class UtilClusters {

    static int PFGRAIN;
    static int PFWORKERS;
    static int nproc;

    float dist(Point p1, Point p2, int dim);

    double gettime();

    void shuffle(Points *points);

    void intshuffle(int *intarray, int length);

    float pspeedy(Points *points, float z, long *kcenter, int pid, pthread_barrier_t *barrier);

    int selectfeasible_fast(Points *points, int **feasible, int kmin, int pid, pthread_barrier_t *barrier);

    double pgain(long x, Points *points, double z, long *numcenters, int pid, pthread_barrier_t *barrier);

    float pkmedian(Points *points, long kmin, long kmax, long *kfinal, int pid, pthread_barrier_t *barrier);

    void *localSearchSub(void *arg_);

    void localSearch(Points *points, long kmin, long kmax, long *kfinal);

    float pFL(Points *points, int *feasible, int numfeasible, float z, long *k, double cost, long iter, float e, int pid,
              pthread_barrier_t *barrier);

    ParallelFor pf;
    ParallelForReduce<double> pfr;

    int pfWorkers;

    bool *switch_membership; //whether to switch membership in pgain
    bool *is_center; //whether a point is a center
    int *center_table; //index table of centers

    //float *block;
    int c, d;
    long kmin, kmax, chunksize;
   // int dim;

public:
    UtilClusters(int pf_workers, long kmin, long kmax); //long kMin, long kMax,
    //~UtilClusters() = delete;


    long findCenters(Points *p);



    /* compute the means for the k clusters */
    int contcenters(Points *points);

    /* copy the centers points in the vector centers*/
    void mycopycenters(Points *points, Points* centers);

    /* prints the time spent in the various functions*/
    void printInfoTime();

};


#endif //PARALLELSTREAMCLUSTER_STREAMCLUSTER_H
