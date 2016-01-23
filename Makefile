
## Makefile for streamcluster project on pc desktop.
#
#
# FF_ROOT     pointing to the FastFlow root directory (i.e. the one containing the ff directory).
FF_ROOT		= /home/dido-ubuntu/fastflow

CXX		= g++ -std=c++11 -DNO_DEFAULT_MAPPING
INCLUDES	= -I $(FF_ROOT)
CXXFLAGS  	=

LDFLAGS 	= -pthread
OPTFLAGS	= -O3 -finline-functions -DNDEBUG

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
