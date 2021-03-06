//
// Created by dido-ubuntu on 09/02/16.
//

#include "Worker.h"


Worker::Worker(int d, long kMIN, long kMAX, long centersz ):
        dim{d}, kmin{kMIN}, kmax{kMAX}, centersize{centersz}, sc(kmin, kmax){ };




Points* Worker::svc(Points *points) {
#ifdef PRINTINFO
    cout<<"Worker "<<get_my_id()<< ": received " << points->num <<"  points" << endl <<flush;
#endif

 long k = sc.findCenters(points);


#ifdef PRINTINFO
    cout<<"Worker " <<get_my_id()<<": finish local search"<<endl;
#endif
    sc.contcenters(points);

#ifdef PRINTINFO
    cout<<"Worker "<<get_my_id()<<": finished cont "<<endl;
#endif

    Points * centers = new Points(dim, centersize);

    float* centerBlock = (float*)malloc(centersize*dim*sizeof(float));

    for( int i = 0; i< centersize; i++ ) {
        centers->p[i].coord = &centerBlock[i*dim];
        centers->p[i].weight = 1.0;
    }

    sc.mycopycenters(points, centers);

#ifdef PRINTINFO
    cout<<"Worker "<<get_my_id()<<": finish copy centers"<<endl;
#endif

    ff_send_out(centers);
    delete points;

    return GO_ON;
}

