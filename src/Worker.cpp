//
// Created by dido-ubuntu on 09/02/16.
//

#include "Worker.h"

Worker::Worker(int d, long kMIN, long kMAX, long centersz):Worker(d, kMIN, kMAX, centersz){ };



Points* Worker::svc(Points *p) {
    ff_send_out(p);
    return GO_ON;
}

