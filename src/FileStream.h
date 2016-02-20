//
// Created by dido-ubuntu on 09/02/16.
//

#ifndef PARALLELSTREAMCLUSTER_FILESTREAM_H
#define PARALLELSTREAMCLUSTER_FILESTREAM_H


#include "PStream.h"

#include <stdlib.h>
#include <iostream>



using namespace std;

class FileStream: public PStream {
public:
    FileStream(char* filename) {
        fp = fopen( filename, "rb");
        if( fp == NULL ) {
            fprintf(stderr,"error opening file %s\n.",filename);
            exit(1);
        }
    }
    size_t read( float* dest, int dim, int num ) {
        return std::fread(dest, sizeof(float)*dim, num, fp);
    }
    int ferror() {
        return std::ferror(fp);
    }
    int feof() {
        return std::feof(fp);
    }
    ~FileStream() {
#ifndef PRINTINFO
        printf("closing file stream\n");
#endif
        fclose(fp);
    }
private:
    FILE* fp;
};



#endif //PARALLELSTREAMCLUSTER_FILESTREAM_H
