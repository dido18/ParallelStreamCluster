//
// Created by dido-ubuntu on 09/02/16.
//

#include "Worker.h"

Worker::Worker(int d, long kMIN, long kMAX, long centersz, long pf_workers):
        dim{d}, kmin{kMIN}, kmax{kMAX}, centersize{centersz}, sc(pf_workers, kmin, kmax){ };




Points* Worker::svc(Points *points) {

    cout<<"Worker "<<get_my_id()<< ": received the points" << endl;

    long k = sc.findCenters(points);

    cout<<"Worker "<<get_my_id()<<": found "<<k<< " centers"<<endl;

    sc.contcenters(points);

    cout<<"Worker "<<get_my_id()<<": finished cont "<<endl;

    Points * centers = new Points(dim, centersize);
    //centers->num = 0; // must be setted to zero initially

    float* centerBlock = (float*)malloc(centersize*dim*sizeof(float));

    for( int i = 0; i< centersize; i++ ) {
        centers->p[i].coord = &centerBlock[i*dim];
        centers->p[i].weight = 1.0;
    }

    sc.mycopycenters(points,centers);

    cout<<"Worker "<<get_my_id()<<": finished copy"<<endl;

    delete points;

    ff_send_out(centers);

    return GO_ON;
}

