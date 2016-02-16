cmake_minimum_required(VERSION 3.3)
project(ParallelStreamCluster)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -std=c++11 -pthread")

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

##add_executable(ParallelStreamCluster ${SOURCE_FILES})

add_executable(ff_streamcluster ${SOURCE_FILES}) #main.cpp


#version with print info
add_executable(ff_streamcluster_print ${SOURCE_FILES}) # main.cpp
target_compile_definitions(ff_streamcluster_print PRIVATE PRINTINFO)


# mic version
add_executable(ff_streamcluster_mic  ${SOURCE_FILES})
set_target_properties(ff_streamcluster_mic PROPERTIES COMPILE_FLAGS "-mmic" )
set_target_properties(ff_streamcluster_mic PROPERTIES LINK_FLAGS "-mmic" )
target_compile_definitions(ff_streamcluster_mic PRIVATE NO_PRINT)
add_custom_command(TARGET ff_streamcluster_mic POST_BUILD COMMAND scp ff_streamcluster_mic mic1:)