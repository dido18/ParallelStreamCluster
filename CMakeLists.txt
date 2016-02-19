cmake_minimum_required(VERSION 3.2)
project(ParallelStreamCluster)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -pthread")

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
        src/Helper.h
        src/Helper.cpp
        src/Collector.cpp
        src/Collector.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

#ff_farm version with print info (host)
add_executable(ff_streamcluster ${SOURCE_FILES})
target_compile_definitions(ff_streamcluster  PRIVATE NO_DEFAULT_MAPPING=1  PROFILE=1)

# ff_farm version from mic version
add_executable(ff_streamcluster_mic  ${SOURCE_FILES})
set_target_properties(ff_streamcluster_mic PROPERTIES COMPILE_FLAGS "-mmic" )
set_target_properties(ff_streamcluster_mic PROPERTIES LINK_FLAGS "-mmic" )
target_compile_definitions(ff_streamcluster_mic PRIVATE NO_PRINT=1 )
add_custom_command(TARGET ff_streamcluster_mic POST_BUILD COMMAND scp "${CMAKE_CURRENT_SOURCE_DIR}/bin/ff_streamcluster_mic" mic0:)

#ff_map parallel
add_executable(ff_streamcluster_map "${CMAKE_CURRENT_SOURCE_DIR}/src_map/ff_streamcluster_map.cpp")

#ff_map parallel on MIC
add_executable(ff_streamcluster_map_mic "${CMAKE_CURRENT_SOURCE_DIR}/src_map/ff_streamcluster_map.cpp")
set_target_properties(ff_streamcluster_map_mic PROPERTIES COMPILE_FLAGS "-mmic" )
set_target_properties(ff_streamcluster_map_mic PROPERTIES LINK_FLAGS "-mmic" )
target_compile_definitions(ff_streamcluster_map_mic PRIVATE NO_PRINT=1 )
add_custom_command(TARGET ff_streamcluster_map_mic POST_BUILD COMMAND scp "${CMAKE_CURRENT_SOURCE_DIR}/bin/ff_streamcluster_map_mic" mic0:)


#rodinia parallel with print (host)
add_executable(rodinia_orig "${CMAKE_CURRENT_SOURCE_DIR}/rodinia_streamcluster/streamcluster_original.cpp")
target_compile_definitions(rodinia_orig  PRIVATE PROFILE=1)

#rodinia parallel mic version
add_executable(rodinia_mic "${CMAKE_CURRENT_SOURCE_DIR}/rodinia_streamcluster/streamcluster_original.cpp")
set_target_properties(rodinia_mic PROPERTIES COMPILE_FLAGS "-mmic" )
set_target_properties(rodinia_mic PROPERTIES LINK_FLAGS "-mmic" )
target_compile_definitions(rodinia_mic PRIVATE PROFILE=1 )
add_custom_command(TARGET rodinia_mic POST_BUILD COMMAND scp "${CMAKE_CURRENT_SOURCE_DIR}/bin/rodinia_mic" mic0:)