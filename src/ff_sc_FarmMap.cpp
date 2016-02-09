

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

//fastflow
#include <ff/parallel_for.hpp>
#include <ff/pipeline.hpp>
#include <ff/farm.hpp>
#include <ff/map.hpp>

using namespace std;
using namespace ff;


#define MAXNAMESIZE 1024 // max filename length
#define SEED 1
/* increase this to reduce probability of random error */
/* increasing it also ups running time of "speedy" part of the code */
/* SP = 1 seems to be fine */
#define SP 1 // number of repetitions of speedy must be >=1

/* higher ITER --> more likely to get correct # of centers */
/* higher ITER also scales the running time almost linearly */
#define ITER 3 // iterate ITER* k log k times; ITER >= 1
#
/* this structure represents a point */
/* these will be passed around to avoid copying coordinates */
typedef struct {
  float weight;
  float *coord;
  long assign;  /* number of point where this one is assigned */
  float cost;  /* cost of that assignment, weight*distance */
} Point;

/* this is the array of points */
typedef struct {
  long num; /* number of points; may not be N if this is a sample */
  int dim;  /* dimensionality */
  Point *p; /* the array itself */
} Points;


class PStream {
public:
  virtual size_t read( float* dest, int dim, int num ) = 0;
  virtual int ferror() = 0;
  virtual int feof() = 0;
  virtual ~PStream() {
  }
};

//synthetic stream
class SimStream : public PStream {
public:
  SimStream(long n_ ) {
    n = n_;
  }
  size_t read( float* dest, int dim, int num ) {
    size_t count = 0;
    for( int i = 0; i < num && n > 0; i++ ) {
      for( int k = 0; k < dim; k++ ) {
	dest[i*dim + k] = lrand48()/(float)INT_MAX;
      }
      n--;
      count++;
    }
    return count;
  }
  int ferror() {
    return 0;
  }
  int feof() {
    return n <= 0;
  }
  ~SimStream() {
  }
private:
  long n;
};

class FileStream : public PStream {
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
    printf("closing file stream\n");
    fclose(fp);
  }
private:
  FILE* fp;
};

// emitter
struct EmitterChunks:ff_node_t<Points>{

  EmitterChunks(PStream *Stream, long cksize, long d): stream(Stream), chunksize(cksize), dim(d){}

  Points *svc (Points *){  //generates the stream

  long IDoffset = 0;

  while(!stream->feof()){
      float* block = (float*)malloc(chunksize*dim*sizeof(float) );
      //float* centerBlock = (float*)malloc(centersize*dim*sizeof(float) );
      //long* centerIDs = (long*)malloc(centersize*dim*sizeof(long));

      if(block == NULL ) {
          	fprintf(stderr,"not enough memory for a chunk!\n");
          	exit(1);
      }

      std::unique_ptr<Points> points((Points *) malloc(sizeof(Points)));
      points->p = (Point *)malloc(chunksize*sizeof(Point));
      points->dim = dim;
    //  points->num = chunksize;

      for(int i = 0; i < chunksize; i++) {
	       (points->p[i]).coord = &block[i*dim];  // points contains pointer to the block array containting the coordinates
      }

      size_t numRead  = stream->read(block, dim, chunksize);

      if(numRead==0) {
	         return EOS;
      }
      fprintf(stderr,"Emitter read %zu points\n", numRead);

      if( stream->ferror() || numRead < (unsigned int)chunksize && !stream->feof() ) {
        	fprintf(stderr, "error reading data!\n");
        	return(EOS);
      }

      points->num = numRead;
      for( int i = 0; i < points->num; i++ ) {
        	points->p[i].weight = 1.0;
        	//points->p[i].ID = IDoffset + i;
      }

      IDoffset +=numRead;

    //  ff_send_out(std::move(points).get());
      ff_send_out(points);
    }
    // the stream is finished
    return EOS;
  } // end svc method

  long chunksize;
  int dim;
  PStream *stream;
};



int main(int argc, char **argv)
{
  char *outfilename = new char[MAXNAMESIZE];
  char *infilename = new char[MAXNAMESIZE];
  long kmin, kmax, n, chunksize, clustersize;
  int dim;

  if (argc<10) {
    fprintf(stderr,"usage: %s k1 k2 d n chunksize clustersize infile outfile nproc\n",
	    argv[0]);
    fprintf(stderr,"  k1:          Min. number of centers allowed\n");
    fprintf(stderr,"  k2:          Max. number of centers allowed\n");
    fprintf(stderr,"  d:           Dimension of each data point\n");
    fprintf(stderr,"  n:           Number of data points\n");
    fprintf(stderr,"  chunksize:   Number of data points to handle per step\n");
    fprintf(stderr,"  clustersize: Maximum number of intermediate centers\n");
    fprintf(stderr,"  infile:      Input file (if n<=0)\n");
    fprintf(stderr,"  outfile:     Output file\n");
    fprintf(stderr,"  nproc:       Number of threads to use\n");
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
 int   nproc = atoi(argv[9]);

  srand48(SEED);
  PStream* stream;
  if( n > 0 ) {
    stream = new SimStream(n);
  }
  else {
    stream = new FileStream(infilename);
  }

  // Fastflow emitter produces the stream of chuncksize elements.
  EmitterChunks emitter(stream, chunksize, dim);
  if(emitter.run_and_wait_end()<0){
    error("error emitter");

  }



  return 0;
}
