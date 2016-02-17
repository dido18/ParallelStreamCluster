#include <iostream>
#include <fstream>
#include <limits.h>
#include <string>
#include <memory>
#include <string.h>


using namespace std;
int MAXNAMESIZE = 100;

int main(int argc, char **argv){

  char *outfilename = new char[MAXNAMESIZE];

  if (argc<3){
      cout <<"usage: argv[0] numPoints  dimension outfilename" << endl;
      exit(1);
  }

  unsigned int NUM = atoi(argv[1]);
  unsigned int DIM = atoi(argv[2]);
  strcpy(outfilename, argv[3]);


  srand48(1);

  auto fp = fopen( outfilename, "w+");
   if( fp == NULL )
      cout << "error";

  float *num = (float*)malloc(sizeof(float)*DIM*NUM);
  for (unsigned long long i=0;i<NUM*DIM;i++)
      num[i] = lrand48()/(float)INT_MAX;

  fwrite(num, sizeof(float)*DIM, NUM, fp);

  fclose(fp);
  /*
  fp = fopen( "test", "r");
  num = (float*)malloc(sizeof(float)*DIM*NUM);
  fread(num, sizeof(float)*DIM, NUM, fp);

  for (int i=0;i<DIM*NUM;i++)
    cout << num[i] << endl;

  fclose(fp);*/
  free(num);
  return 0;
}
