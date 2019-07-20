cmake_minimum_required(VERSION 3.12)
project(mysqlpp)

set(MYSQLPP_VERSION_MAJOR 3)
set(MYSQLPP_VERSION_MINOR 2)
set(MYSQLPP_VERSION_BUGFIX 1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

option(FIELD_LIMIT "set max template query and SSQLS field count" 10)
option(MYSQLPP_OLD_CLASS_NAMES "Enables MySQL old class names")

find_package(MySQL REQUIRED)
find_package (Threads)

include_directories(${MySQL_INCLUDE_DIR})

include(CheckFunctionExists)
check_function_exists(localtime_r HAVE_LOCALTIME_R)
check_function_exists(localtime_s MYSQLPP_HAVE_LOCALTIME_S)
check_function_exists(getopt HAVE_POSIX_GETOPT)

check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(synch.h HAVE_SYNCH_H)
check_include_file(libiberty.h HAVE_LIBIBERTY_GETOPT)

if(CMAKE_THREAD_LIBS_INIT)
  set(HAVE_THREADS TRUE)
endif()

if(CMAKE_USE_PTHREADS_INIT)
  set(HAVE_PTHREAD TRUE)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(MYSQLPP_PLATFORM_VISUAL_CPP TRUE)
endif()

configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(lib)
