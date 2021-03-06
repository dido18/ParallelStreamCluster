//
// Created by dido-ubuntu on 09/02/16.
//

#include "Emitter.h"
#include "Helper.h"


//#define PROFILE


using namespace std;
using namespace ff;

Emitter::Emitter(PStream *Stream, long cksize, long d) :
        stream(Stream), chunksize(cksize), dim(d) { }

Points *Emitter::svc(Points *p) {

    while (1) {

        float *block = (float *) malloc(chunksize * dim * sizeof(float));
        if (block == NULL) {
            fprintf(stderr, "not enough memory for a chunk!\n");
            exit(1);
        }

        Points *points = new Points(dim, chunksize);

        for (int i = 0; i < chunksize; i++) {
            points->p[i].coord = &block[i * dim];  // points contains pointer to the block array containting the coordinates
        }

        size_t numRead = stream->read(block, dim, chunksize);

        if(numRead==0){
            break;
        }

#ifdef PRINTINFO
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

        IDoffset += numRead;

        ff_send_out(points);
        if (stream->feof()) {
            break;
        }
    }

    return EOS;   // the stream is finished
};

