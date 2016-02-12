cmake_minimum_required(VERSION 2.8)
project(ParallelStreamCluster)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

include_directories(~/fastflow)
set(SOURCE_FILES
        src/main.cpp
        src/Points.h
        src/UtilClusters.cpp
        src/UtilClusters.h
        src/Worker.cpp
        src/Worker.h
        src/Emitter.cpp
        src/Emitter.h
        src/PStream.h
        src/FileStream.h
        src/SimStream.h
        src/Globals.h
        src/Helper.h src/Collector.cpp src/Collector.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_executable(ParallelStreamCluster ${SOURCE_FILES})