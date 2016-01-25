
## Makefile for streamcluster project on pc desktop.
#
#
# FF_ROOT     pointing to the FastFlow root directory (i.e. the one containing the ff directory).
FF_ROOT		= /home/dido-ubuntu/fastflow

# prefix of the project directory 
PREFIX          = /home/dido-ubuntu/github/ParallelStreamCluster

CXX		= g++ -std=c++11 -DNO_DEFAULT_MAPPING
INCLUDES	= -I $(FF_ROOT)
CXXFLAGS  	= -g

LDFLAGS 	= -pthread
OPTFLAGS	= -O3 -finline-functions -DNDEBUG  #-DPRINTINFO

TARGETS		= ff_stream_cluster

.PHONY: all clean cleanall
.SUFFIXES: .cpp


%: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ $< $(LDFLAGS)

all		: $(TARGETS)
clean		:
	rm -f $(TARGETS)
cleanall	: clean
	\rm -f *.o *~

install:
	mkdir -p $(PREFIX)/bin
	cp -f $(TARGETS) $(PREFIX)/bin/$(TARGETS)
