cmake_minimum_required(VERSION 2.8)

project(libindiserver C CXX)

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

##################  INDI version  ################################
set(INDI_SOVERSION "1")
set(CMAKE_INDI_VERSION_MAJOR 1)
set(CMAKE_INDI_VERSION_MINOR 2)
set(CMAKE_INDI_VERSION_RELEASE 0)
set(CMAKE_INDI_VERSION_STRING "${CMAKE_INDI_VERSION_MAJOR}.${CMAKE_INDI_VERSION_MINOR}.${CMAKE_INDI_VERSION_RELEASE}")

#paths
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")
set(DATA_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share/indi/")
set(BIN_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include")

IF(APPLE)
set(CMAKE_SHARED_LINKER_FLAGS "-undefined dynamic_lookup")
ENDIF(APPLE)

##################  setup install directories  ################################
set (LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
set (LIB_DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}")
## the following are directories where stuff will be installed to
set(INCLUDE_INSTALL_DIR      "${CMAKE_INSTALL_PREFIX}/include/")

#Indi
find_package(INDI REQUIRED)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h )
include_directories( ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${INDI_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(libindiserver_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/libindiserver.c ${CMAKE_CURRENT_SOURCE_DIR}/fq.c)

add_library(indiserver SHARED ${libindiserver_SRCS})
SET_TARGET_PROPERTIES(indiserver PROPERTIES COMPILE_FLAGS "-fPIC")
target_link_libraries(indiserver ${INDI_LIBRARIES})

install(TARGETS indiserver LIBRARY DESTINATION ${LIB_DESTINATION})
set_target_properties(indiserver PROPERTIES VERSION ${CMAKE_INDI_VERSION_STRING} SOVERSION ${INDI_SOVERSION})
install( FILES libindiserver.h fq.h DESTINATION ${INCLUDE_INSTALL_DIR}/libindi COMPONENT Devel) 