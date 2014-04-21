cmake_minimum_required( VERSION 2.8 )

include_directories( SYSTEM ${OpenCV_INCLUDE_DIRS} )
include_directories( ${ImageProcCV_HEADERS} )

file( GLOB ImageProcCV_SRC "*.cpp" )

message ( STATUS "${ImageProcCV_SRC}" )

add_library(ImageProcCV SHARED ${ImageProcCV_SRC} )

#SET_TARGET_PROPERTIES(ImageProcCV PROPERTIES LINKER_LANGUAGE C++)

target_link_libraries (ImageProcCV ${OpenCV_LIBS} )
