#include <stdio.h>
#include <iostream>
#include <ff/farm.hpp>
#include <ff/pipeline.hpp>

/*
  ff_stream_cluster.cpp receive a streams of points.
      The EmitterChunks groups the stream in chuncks of size chunksize and  sent them to the workers.

 */

using namespace std;

using namespace ff;

#define MAXNAMESIZE 1024 // max filename length


/* this structure represents a point */
/* these will be passed around to avoid copying coordinates */

// common C idiom to avoid having to write "struct S"
// typedef struct {int a; int b;} Point, *pPoint;
//  Point * p1; pPoint ps2   //are two objects with the same types
struct Point{
  //  Point(float weight, float* coord, long assign, float cost):
  float weight;
  float *coord;
  long assign;  /* number of point where this one is assigned */
  float cost;  /* cost of that assignment, weight*distance */
};

/* this is the array of points */
struct Points {
  Points(int d, long n, Point* point):num(n),dim(d),p(point){}

  long num; /* number of points; may not be N if this is a sample */
  int dim;  /* dimensionality */
  Point *p; /* the array itself */
};


/* general class for different types of  stream*/
class PStream {
public:
  virtual size_t read( float* dest, int dim, int num ) = 0;
  virtual int ferror() = 0;
  virtual int feof() = 0;
  virtual ~PStream() {
  }
};




struct EmitterChunks:ff_node_t<Points>{

  EmitterChunks(PStream *Stream, long cksize, long d): stream(Stream), chunksize(cksize), dim(d){}

  Points *svc (Points *){ //  it will receive the streams from the external source

    float* block = (float*)malloc(chunksize*dim*sizeof(float) );
    //float* centerBlock = (float*)malloc(centersize*dim*sizeof(float) );
    //long* centerIDs = (long*)malloc(centersize*dim*sizeof(long));

    if( block == NULL ) {
      fprintf(stderr,"not enough memory for a chunk!\n");
      exit(1);
    }

  
    Point * p = (Point *)malloc(chunksize*sizeof(Point));
    //Point * p = new Point[chunksize];
    Points *points = new Points(dim, chunksize, p);

    for( int i = 0; i < chunksize; i++ ) {
      points->p[i].coord = &block[i*dim];
    }

    bool endStream = false;
    while(endStream == false){
          size_t numRead  = stream->read(block, dim, chunksize);
	  endStream = (numRead == 0);
	  fprintf(stderr,"\n Emitter read %d points\n", numRead);

	  if( stream->ferror() || numRead < (unsigned int)chunksize && !stream->feof() ) {
	    fprintf(stderr, "error reading data!\n");
	    return(EOS);
	  }

	  points->num = numRead;
	  for( int i = 0; i < points->num; i++ ) {
	    points->p[i].weight = 1.0;
	  }

	  ff_send_out(points);
  }//end strem 
	  return EOS;
  } // end svc method

  long chunksize;
  int dim;
  PStream *stream;
};


/* worker receive a chunk and produce k centers of the chunk received.*/
struct Worker:ff_node_t<Points>{

  Points *svc(Points* p){
    std::cout << "The worker " << get_my_id()<<" has received a chunk with " << p->num << " points " <<" \n";
    return p;
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
	dest[i*dim + k] = lrand48()/(float)INT_MAX; //array num points generater of  dim dimensions.
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

// FileStream generate a stream froma file.
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
    fprintf(stderr,"closing file stream\n");
    fclose(fp);
  }
private:
  FILE* fp;
};


int main (int argc, char *argv[]){

  char *outfilename = new char[MAXNAMESIZE];
  char *infilename = new char[MAXNAMESIZE];
  long kmin, kmax, n, chunksize, clustersize;
  int dim, nWorkers;

   if (argc<10) {
    fprintf(stderr,"usage: %s  k1 k2 d n chunksize clustersize infile outfile nproc\n",argv[0]);
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
  nWorkers = atoi(argv[9]);

  PStream* stream;
  if( n > 0 ) {
    stream = new SimStream(n);
  }
  else {
    stream = new FileStream(infilename);
  }

  EmitterChunks emitter(stream, chunksize, dim);    //(PStream *Stream, long chuncksize, long dim)
  /*
  ff_Farm<Points,Points> myFarm([nWorkers](){
      std::vector<std::unique_ptr<ff_node>>Workers;
      for(int i=0; i< nWorkers; i++){
	Workers.push_back(make_unique<Worker>());
      }
      return Workers;
    }());
  */

  std::vector<std::unique_ptr<ff_node>> Workers;
  for( int i=0; i<nWorkers; ++i){
    Workers.push_back(make_unique<Worker>());
  }
  ff_Farm<Points> myFarm (std::move(Workers),emitter);

  if (myFarm.run_and_wait_end()<0) {
        error("running farm\n");
        return -1;
	}
  return(0);
}
