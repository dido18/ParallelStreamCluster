
## Makefile for streamcluster project on pc desktop.
#
#
# FF_ROOT     pointing to the FastFlow root directory (i.e. the one containing the ff directory).
FF_ROOT		= ~/fastflow


# prefix of the project directory
#PREFIX          = /home/dido-ubuntu/github/ParallelStreamCluster

#
CXX		= g++ -std=c++11

INCLUDES	= -I $(FF_ROOT)
CXXFLAGS  	= -g 		#for gdb debugging

LDFLAGS 	= -pthread

OPTFLAGS	= -O3        #-DPRINTINFO  # -finline-functions -DNDEBUG  #-DPRINTINFO

TARGETS		=  ff_stream_cluster_FarmMap # ff_stream_cluster_Map ff_stream_cluster


.PHONY: all clean cleanall install 
.SUFFIXES: .cpp

%:%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ $< $(LDFLAGS)

all : $(TARGETS) install

clean :
	rm -f $(TARGETS)
cleanall : clean
	\rm -f *.o *~

install:
	mkdir -p ../bin
	mv -f $(TARGETS) ../bin/
