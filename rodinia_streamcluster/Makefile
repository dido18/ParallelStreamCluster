PREFIX=${PARSECDIR}/pkgs/kernels/streamcluster/inst/${PARSECPLAT}

TARGET_C = rodinia_original

TARGET_O = rodinia_omp

# ifdef version
#  ifeq "$(version)" "parallel"
#    CXXFLAGS :=	$(CXXFLAGS) -DENABLE_THREADS -pthread
#  endif
# endif

CXX=g++
LDFLAGS=
CXXFLAGS= -O3

all: original omp

original:
	$(CXX) $(CXXFLAGS)  streamcluster_original.cpp -o $(TARGET_C) -DENABLE_THREADS -pthread

omp:
	$(CXX)  $(CXXFLAGS) streamcluster_omp.cpp  -o $(TARGET_O) -fopenmp


clean:
	rm -f *.o *~ *.txt rodinia_original rodinia_omp

# dido: run install to put the binary inside /bin in the project
install:
		mkdir -p ../bin
		mv -f $(TARGET_O) ../bin/
		mv -f $(TARGET_C) ../bin/
