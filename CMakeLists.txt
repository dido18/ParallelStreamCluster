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


#ff_farm version with print info (HOST)
add_executable(ff_streamcluster_farm ${SOURCE_FILES})
target_compile_definitions(ff_streamcluster_farm  PRIVATE NO_DEFAULT_MAPPING=1 PRINTINFO) #PRINTINFO PROFILE=1

#ff_map parallel on HOST
add_executable(ff_streamcluster_map "${CMAKE_CURRENT_SOURCE_DIR}/src_map/ff_streamcluster_map.cpp")
target_compile_definitions(ff_streamcluster_map  PRIVATE NO_DEFAULT_MAPPING=1  PROFILE PRINTINFO)

# ff_farm version on MIC
add_executable(ff_streamcluster_farm_mic  ${SOURCE_FILES})
set_target_properties(ff_streamcluster_farm_mic PROPERTIES COMPILE_FLAGS "-mmic" )
set_target_properties(ff_streamcluster_farm_mic PROPERTIES LINK_FLAGS "-mmic" )
target_compile_definitions(ff_streamcluster_farm_mic PRIVATE NO_DEFAULT_MAPPING PROFILE=0 )
add_custom_command(TARGET ff_streamcluster_farm_mic POST_BUILD COMMAND scp "${CMAKE_CURRENT_SOURCE_DIR}/bin/ff_streamcluster_farm_mic" mic0:)


#ff_map parallel on MIC
add_executable(ff_streamcluster_map_mic "${CMAKE_CURRENT_SOURCE_DIR}/src_map/ff_streamcluster_map.cpp")
set_target_properties(ff_streamcluster_map_mic PROPERTIES COMPILE_FLAGS "-mmic" )
set_target_properties(ff_streamcluster_map_mic PROPERTIES LINK_FLAGS "-mmic" )
target_compile_definitions(ff_streamcluster_map_mic PRIVATE)
add_custom_command(TARGET ff_streamcluster_map_mic POST_BUILD COMMAND scp "${CMAKE_CURRENT_SOURCE_DIR}/bin/ff_streamcluster_map_mic" mic0:)


#rodinia parallel with print (host)
#add_executable(rodinia_orig "${CMAKE_CURRENT_SOURCE_DIR}/rodinia_streamcluster/streamcluster_original.cpp")
#target_compile_definitions(rodinia_orig  PRIVATE PROFILE=1)

#rodinia parallel MIC
#add_executable(rodinia_mic "${CMAKE_CURRENT_SOURCE_DIR}/rodinia_streamcluster/streamcluster_original.cpp")
#set_target_properties(rodinia_mic PROPERTIES COMPILE_FLAGS "-mmic" )
#set_target_properties(rodinia_mic PROPERTIES LINK_FLAGS "-mmic" )
#target_compile_definitions(rodinia_mic PRIVATE PROFILE=1 )
#add_custom_command(TARGET rodinia_mic POST_BUILD COMMAND scp "${CMAKE_CURRENT_SOURCE_DIR}/bin/rodinia_mic" mic0:)