cmake_minimum_required(VERSION 2.8)
project(pocotest)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules"
  )

include(FindPoco)

find_package(Poco REQUIRED Foundation)
include_directories(${Poco_DIR})

include_directories(include/)

add_executable(test example/example.cpp)
add_library(plugin1 SHARED example/plugin1.cpp)

target_link_libraries(test ${Poco_LIBRARIES})
