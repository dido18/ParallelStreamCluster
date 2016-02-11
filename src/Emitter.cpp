//
// Created by dido-ubuntu on 09/02/16.
//

#include "Emitter.h"
//#include <memory>

//#include "HelperStreamCluster.h"
#include "Helper.h"

using namespace std;
using namespace ff;

Emitter::Emitter(PStream *Stream, long cksize, long d, long kmin, long kmax, int pf_workers)  :
        stream(Stream), chunksize(cksize), dim(d), sc(pf_workers, kmin, kmax) { }

Points* Emitter::svc(Points * points) {
        while (!stream->feof()) {
            float *block = (float *) malloc(chunksize * dim * sizeof(float));
            //float* centerBlock = (float*)malloc(centersize*dim*sizeof(float) );
            //long* centerIDs = (long*)malloc(centersize*dim*sizeof(long));

            if (block == NULL) {
                fprintf(stderr, "not enough memory for a chunk!\n");
                exit(1);
            }

///            unique_ptr<Points> points(new Points(dim, chunksize));
            Points * points = new Points(dim, chunksize);

            for (int i = 0; i < chunksize; i++) {
                (points->p[i]).coord = &block[i * dim];  // points contains pointer to the block array containting the coordinates
            }

            size_t numRead = stream->read(block, dim, chunksize);

            /*if (numRead == 0) {
                ff_send_out(EOS);
            }*/

            cout << "Emitter reads  " << numRead << " points" << endl;

            if (stream->ferror() || numRead < (unsigned int) chunksize && !stream->feof()) {
                fprintf(stderr, "error reading data!\n");
                break; //can be EOS ??
            }

            points->num = numRead;
            for (int i = 0; i < points->num; i++) {
                points->p[i].weight = 1.0;
                points->p[i].ID = IDoffset + i;
            }

            IDoffset += numRead;


            long k = sc.findCenters(points);//, kmin, kmax,dim);// centersize);
           // points->to_string();

            cout<<" found "<<k<< " centers"<<endl;

            sc.contcenters(points);
            cout<<" finished cont "<<endl;

            Points * centers = new Points(dim, chunksize);
            centers->num = 0; // must be setted to zero initially

            float* centerBlock = (float*)malloc(chunksize*dim*sizeof(float) );

            for( int i = 0; i< chunksize; i++ ) {
                centers->p[i].coord = &centerBlock[i*dim];
                centers->p[i].weight = 1.0;
            }


            sc.mycopycenters(points,centers);
            cout<<" finished copy"<<endl;
            centers->to_string();

            ff_send_out(points);
        }


       return EOS;   // the stream is finished
};

int Emitter::run_and_wait_end(bool b){
    if(ff_node_t::run()<0) return -1;
    return ff_node_t::wait();
}
