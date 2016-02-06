# Makefile for streamcluster

PREFIX=${PARSECDIR}/pkgs/kernels/streamcluster/inst/${PARSECPLAT}

TARGET=streamcluster
OBJS=streamcluster.o


#THRREAD version
CXXFLAGS :=	$(CXXFLAGS) -g -DENABLE_THREADS -pthread -DPROFILE  -O3
OBJS += parsec_barrier.o

#ifdef version
#  ifeq "$(version)" "pthreads"
#    CXXFLAGS :=	$(CXXFLAGS) -DENABLE_THREADS -pthread
#    OBJS += parsec_barrier.o
#  endif
#  ifeq "$(version)" "tbb"
#    CXXFLAGS := $(CXXFLAGS) -DTBB_VERSION
#    LIBS := $(LIBS) -ltbb
#  endif
#endif

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)

install:
	mkdir -p ../bin
	mv -f $(TARGET) ../bin/
