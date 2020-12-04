cmake_minimum_required(VERSION 3.15)
project(OptimizedCXX)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    set(ENV{_NO_DEBUG_HEAP} 1)
    add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
endif()

#
# common
#
add_library(common
    STATIC src/stopwatch.h
           src/stopwatch03.h
           src/stopwatch03.cpp
           src/stopwatch11.h
           src/stopwatch11.cpp
           src/priority_thread.h
           src/test_driver.h
           src/test_driver.cpp
           src/Win32.cpp)

#
# strings
#
add_executable(strings src/strings.h src/strings.cpp)
target_link_libraries(strings common)