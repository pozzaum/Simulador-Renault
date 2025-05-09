
# define build type
#SET( CMAKE_BUILD_TYPE Debug )

PROJECT(fparser CXX)

cmake_minimum_required(VERSION 2.8)

# default
set(LIB_VERSION_MAJOR 4)
set(LIB_VERSION_MINOR 5)
set(LIB_VERSION_PATCH 1)
set(LIB_VERSION_STRING ${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH})

set(VERSION "v${LIB_VERSION_STRING}")

# if(APPLE AND NOT CMAKE_INSTALL_NAME_DIR)
#   set(CMAKE_INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}")
# endif()

set(HEADERS fparser.hh fpconfig.hh extrasrc/fptypes.hh extrasrc/fpaux.hh)
set(SOURCES fparser.cc fpoptimizer.cc)

remove(CMAKE_CXX_FLAGS -Dfparser_EXPORTS)

ADD_LIBRARY(fparser ${SOURCES} ${HEADERS})

set_target_properties(fparser PROPERTIES VERSION ${LIB_VERSION_STRING} SOVERSION ${LIB_VERSION_MAJOR})

INSTALL(TARGETS fparser DESTINATION lib${LIB_SUFFIX})

INSTALL(FILES fparser.hh DESTINATION include)

target_include_directories(fparser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

