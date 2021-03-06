cmake_minimum_required(VERSION 2.8)

project(swig-libinditcl)

#paths
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")

#swig
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

#TCL
find_package(TCL REQUIRED)
include_directories(${TCL_INCLUDE_PATH})

#INDI
set(INDI_SRC_DIR "/home/geehale/svnprojects/sourceforge/indi-code/libindi")
#include_directories(${INDI_SRC_DIR})
find_package(INDI)
include_directories(${INDI_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#Build
set(CMAKE_SWIG_FLAGS "-c++" "-Wall")

#SET_SOURCE_FILES_PROPERTIES(baseclient.i PROPERTIES CPLUSPLUS ON)
#SET_SOURCE_FILES_PROPERTIES(baseclient.i PROPERTIES SWIG_FLAGS "-includeall")
#SWIG_ADD_MODULE(indiclienttcl tcl baseclient.i ${INDI_SRC_DIR}/libs/indibase/baseclient.cpp)

# INDI::Baseclient is abstract, so SWIG does not generate constructor
#SET_SOURCE_FILES_PROPERTIES(baseclient.i PROPERTIES CPLUSPLUS ON)
#SWIG_ADD_MODULE(indiclienttcl tcl baseclient.i)

# Create a BaseClient derived class which implements every virtual methods 
SET_SOURCE_FILES_PROPERTIES(tclclient.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(tclclient.cpp PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(indiclienttcl tcl tclclient.i tclclient.cpp)

SWIG_LINK_LIBRARIES(indiclienttcl ${TCL_LIBRARY} ${INDI_CLIENT_LIBRARIES} -lindi -lz)