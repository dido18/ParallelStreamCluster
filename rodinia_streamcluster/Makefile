PREFIX=${PARSECDIR}/pkgs/kernels/streamcluster/inst/${PARSECPLAT}

TARGET_C = sc_cpu

TARGET_O = sc_omp

ifdef version
  ifeq "$(version)" "parallel"
    CXXFLAGS :=	$(CXXFLAGS) -DENABLE_THREADS -pthread
  endif
endif

all: cpu omp

cpu:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) streamcluster_original.cpp -o $(TARGET_C) $(LIBS) -DENABLE_THREADS -pthread

omp:
	g++ -O3 -fopenmp -o $(TARGET_O) streamcluster_omp.cpp


clean:
	rm -f *.o *~ *.txt sc_cpu sc_omp

# dido: run install to put the binary inside /bin in the project
install:
		mkdir -p ../bin
		mv -f $(TARGET_O) ../bin/
		mv -f $(TARGET_C) ../bin/
