cmake_minimum_required(VERSION 2.8)
project(ParallelStreamCluster)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

include_directories(~/fastflow)
set(SOURCE_FILES
        src/main.cpp
        #src/HelperStreamCluster.h
        src/Points.h
       # src/StreamCluster++.h
        src/StreamCluster.h
        src/StreamCluster.cpp
        src/Worker.cpp
        src/Worker.h
        src/Emitter.cpp
        src/Emitter.h
        src/PStream.h
        src/FileStream.h
        src/SimStream.h
        src/Globals.h
        src/Helper.h)


add_executable(ParallelStreamCluster ${SOURCE_FILES})