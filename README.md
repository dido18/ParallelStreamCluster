# ParallelStreamCluster
StreamCluster is an application computing a clustering algorithm over data coming from an input stream. Data clustering is used in a variety of different applications and basically consists in grouping the incoming data in such a way all belong to a given cluster (group of data) with a given centroid item.

We will consider here the application already provided in the [Parsec](http://parsec.cs.princeton.edu/ "Parsec web site") benchmark suite. The application is provided as C source code. Different parallelisations of the code exist (e.g. using TBB in parsec, or OpenMP and Cuda in the Rodinia benchmark suite).

The student must develop a parallel version of the application using [FastFlow](http://calvados.di.unipi.it/ "FastFlow web site").

The project must be developed with:
- processes and COW (cluster of workstation computation)


## StreamCLuster() function


```
void streamCluster( stream,kmin,  kmax, dim, chunksize, centersize, char* outfile ){

init centers[centersize]
init points[chunksize]

while(EndOfStream){
	reads chuncksize points and put into points[]
   selects k centers  in points[] (localsearch() uses pgain()) //data parallel
	update weight for the k clusters (contcenters())
	if( k + len(center) > centersize)
		exit no more space for centers.
	else
		add k centers to centers[]
}

selects k centers from centers[] with localSearc().
}
```

### pgain function
- The program spends most of its time evaluating the
gain of opening a new center. This operation uses a paral-
lelization scheme which employs static partitioning of data
points.
- The parallel gain computation is implemented in function
`pgain`. Given a preliminary solution, the function computes
how much cost can be saved by opening a new center. For
every new point, it weighs the cost of making it a new center
and reassigning some of the existing points to it against the
savings caused by minimizing the distance between points.


`double pgain(long x, Points *points, double z, long int *numcenters, int pid, pthread_barrier_t* barrier)
`
If the heuristic determines that the change would be advantageous the
results are committed.


# PARSEC framework - streamcluster

For running the **streamcluster** application with the PARSEC benchmark use the command belove.

You must use the `/bin/bash` shell in order to have the variables environment.
````
parsecmgmt -a run -p streamcluster  //use simple test suite
```

```
parsecmgmt -a run -p streamcluster -i simlarge
```

for removing all the compiled files
```
parsecmgmt -a uninstall -p streamCluster
```
builds and compiles stream luster
```
parsecmgmt -a build -p streamcluster
```

### Output parsec
The output of the streamparallel in PARSEC with **test** imput is a list of centers found:

```
3			// ID center (first)
6.000000		// weight of  the center
0.231290 		// coordinata of the center (in this case one)

6
4.000000
0.785309


```


#### Structure of Parsec benchmark
PARSEC folder has the following structure:
```
paresec-3.0
	bin/		directory with PARSEC tools
	config/		global configuration
	log/		log files of builds and runs (dynamically created)
	man/		man pages of the PARSEC distribution
	pkgs/		package groups which contain the packages
	version		file with version number of PARSEC distribution
```

A package has the following directory structure:
```
pkgs/kernel/streamcluster

	inputs/		directory with input archives (optional)
	inst/		installation directory (dynamically created)
	obj/		build directory (dynamically created)
	outputs/	directory with reference outputs (optional)
	parsec/		PARSEC configuration files
	run/		directory for program execution (dynamically created)
	src/		source code of the package
	version		file with package version
```

# Use streamcluster alone

```
usage: ./streamcluster k1 k2 d n chunksize clustersize infile outfile nproc
  k1:          Min. number of centers allowed
  k2:          Max. number of centers allowed
  d:           Dimension of each data point
  n:           Number of data points
  chunksize:   Number of data points to handle per step
  clustersize: Maximum number of intermediate centers
  infile:      Input file (if n<=0)
  outfile:     Output file
  nproc:       Number of threads to use

if n > 0, points will be randomly generated instead of reading from infile.
```
