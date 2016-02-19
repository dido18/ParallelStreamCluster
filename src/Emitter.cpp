//
// Created by dido-ubuntu on 09/02/16.
//

#include "Emitter.h"
#include "Helper.h"


#define PROFILE
//#define NO_PRINT

#ifdef PROFILE
    double arrival_time=0;
    double arrival_count=0;
#endif


using namespace std;
using namespace ff;

Emitter::Emitter(PStream *Stream, long cksize, long d, long kmin, long kmax, int pf_workers) :
        stream(Stream), chunksize(cksize), dim(d), sc(pf_workers, kmin, kmax) { }

Points *Emitter::svc(Points *p) {


    while (1) {
#ifdef PROFILE
        double t0 = Helper::gettime();
#endif

        float *block = (float *) malloc(chunksize * dim * sizeof(float));
        if (block == NULL) {
            fprintf(stderr, "not enough memory for a chunk!\n");
            exit(1);
        }
///         unique_ptr<Points> points(new Points(dim, chunksize));
        Points *points = new Points(dim, chunksize);

        for (int i = 0; i < chunksize; i++) {
            points->p[i].coord = &block[i * dim];  // points contains pointer to the block array containting the coordinates
        }

        size_t numRead = stream->read(block, dim, chunksize);

        if(numRead==0){
            break;
        }

        //dido
      //  for (int i = 0; i < chunksize * dim; ++i) {
       //     cout << i << " " << block[i] << endl;
       // }
#ifndef NO_PRINT
        cout << "Emitter reads  " << numRead << " points" << endl << flush;
#endif
        if (stream->ferror() || numRead < (unsigned int) chunksize && !stream->feof()) {
            fprintf(stderr, "error reading data!\n");
            break;
        }


        points->num = numRead;
        for (int i = 0; i < points->num; i++) {
            points->p[i].weight = 1.0;
            points->p[i].ID = IDoffset + i;
        }
        //cout<< "======= emitter points ===================="<< endl;
        //points->to_string();
        //cout<< "======= end emitter points ================"<< endl;

        IDoffset += numRead;
#ifdef PROFILE
        arrival_count++;
        arrival_time += Helper::gettime() - t0;
#endif

        ff_send_out(points);
        if (stream->feof()) {
            break;
        }
    }


    return EOS;   // the stream is finished
};

void Emitter::svc_end(){

    Helper::TIME_ARRIVAL = arrival_time / arrival_count;

#ifndef NO_PRINT
    cout <<"Arrival time " <<arrival_time/arrival_count << " s" << endl;
#endif
}

