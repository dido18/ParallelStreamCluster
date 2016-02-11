//
// Created by dido-ubuntu on 09/02/16.
//


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <memory>

#include "PStream.h"
#include "SimStream.h"
#include "FileStream.h"
#include "Points.h"
#include "Helper.h"
#include "Emitter.h"
#include "Worker.h"

//fastflow
#include <ff/farm.hpp>

#define MAXNAMESIZE 1024 // max filename length
#define SEED 1

//int  FARM_WORKERS ; // number of workers in the farm
//int  PFWORKERS = 1 ;   // parallel_for parallelism degree

int  PFGRAIN = 1 ;     // dafualt static scheduling of iterations

using namespace ff;
using namespace std;
using namespace helper;

int main(int argc, char **argv) {
    char *outfilename = new char[MAXNAMESIZE];
    char *infilename = new char[MAXNAMESIZE];
    long kmin, kmax, n, chunksize, clustersize;
    int dim;

    // this variable are needed by streamcluster ++
    int c = 0;
    int d = 0;


    if (argc<11) {
        fprintf(stderr,"usage: %s k1 k2 d n chunksize clustersize infile outfile farmWorkers mapWorkers \n",  argv[0]);
        fprintf(stderr,"  k1:          Min. number of centers allowed\n");
        fprintf(stderr,"  k2:          Max. number of centers allowed\n");
        fprintf(stderr,"  d:           Dimension of each data point\n");
        fprintf(stderr,"  n:           Number of data points\n");
        fprintf(stderr,"  chunksize:   Number of data points to handle per step\n");
        fprintf(stderr,"  clustersize: Maximum number of intermediate centers\n");
        fprintf(stderr,"  infile:      Input file (if n<=0)\n");
        fprintf(stderr,"  outfile:     Output file\n");
        fprintf(stderr,"  farmWorkers: Number of workers to use in the farm\n");
        fprintf(stderr,"  pfWorkers:   Number of workers to use in the parallel for\n");
        fprintf(stderr,"\n");
        fprintf(stderr, "if n > 0, points will be randomly generated instead of reading from infile.\n");
        exit(1);
    }
    kmin = atoi(argv[1]);
    kmax = atoi(argv[2]);
    dim = atoi(argv[3]);
    n = atoi(argv[4]);
    chunksize = atoi(argv[5]);
    clustersize = atoi(argv[6]);
    strcpy(infilename, argv[7]);
    strcpy(outfilename, argv[8]);

    int FARM_WORKERS = atoi(argv[9]);
    long PFWORKERS =  atoi(argv[10]);

    PFGRAIN = 0;
    //nproc = 1; // must be present in the original file implementation


    srand48(SEED);
    PStream* stream;
    if( n > 0 ) {
        stream = new SimStream(n);
    }
    else {
        stream = new FileStream(infilename);
    }

    // emitter produces the stream of chuncksize points
    Emitter *emitter = new Emitter(stream, chunksize, dim, kmin, kmax, PFWORKERS);


   // if(emitter.run_and_wait_end() <0)
    //    error ("running emitter");

        std::vector<ff_node *> Workers;
        for(int i =0; i < FARM_WORKERS; ++i ) {//(int d, long kMIN, long kMAX, long centersz, long pf_workers)
            Workers.push_back(new Worker(dim,kmin,kmax,clustersize,PFWORKERS));
        }
       ff_farm<> myFarm(Workers,emitter);

        if(myFarm.run_and_wait_end()<0){
            error("running farm");
        }

/*
    // workers finds the  medians in the stream received.
    vector<unique_ptr<ff_node>> Workers;

    for(int i=0; i<FARM_WORKERS; ++i){
        Workers.push_back(unique_ptr<Worker>(new Worker(dim, kmin, kmax, clustersize,PFWORKERS));
        //(int d, long kMIN, long kMAX, long centersz )
    }

    // Fastflow Farm declaration
    ff_Farm<Points> myFarm (move(Workers));//std::move(Workers), emitter);
    myFarm.remove_collector(); // remove the default collector
*/
    //Collector
    //lastStage Collector(dim,kmin,kmax,outfilename,clustersize);//long kMIN, long kMAX, char* out, long clustersz);

    //Pipe of farm and my collector
    //ff_Pipe<Points> myPipe(myFarm, Collector);
/*
    double t1 = gettime();
    if (myFarm.run_and_wait_end()<0) {
        error("running Pipe\n");
        return -1;
    }
    double t2 = gettime();


    printf("time = %lf\n",t2-t1);
*/

    delete stream;

    return 0;

}
