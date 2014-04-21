#minimum version for CMake
cmake_minimum_required(VERSION 2.6)


#project name
project(ImageProcCV)


#see if we are in Mac
if ( CMAKE_GENERATOR STREQUAL Xcode )
  set( CMAKE_GENERATOR_IS_XCODE true )
endif()

# Check if platform is 64 bit
if( CMAKE_SIZEOF_VOID_P EQUAL 4 )
  set( 64_BIT_PLATFORM 0 )
else()
  set( 64_BIT_PLATFORM 1 )
endif()

# Force release build by default, speed is of the essence
if ( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release )
endif()

#include path for ImageProcCV headers

set( ImageProcCV_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include CACHE PATH "Path to ImageProcCV headers" )
#Find OpenCV libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)
find_package( OpenCV REQUIRED )

#if ( OpenCV_FOUND )
#   message ( STATUS,"OpenCV found" )
#   message ( STATUS, "${OpenCV_LIBRARIES}" )
#   message ( STATUS, "${OpenCV_INCLUDE_DIRS}" )
#else ()
#   message ( FATAL_ERROR,"OpenCV Not Found" )
#endif()
#include_directories("${OpenCV_INCLUDE_DIRS}")

#sub directories
add_subdirectory( src )
add_subdirectory( include )



