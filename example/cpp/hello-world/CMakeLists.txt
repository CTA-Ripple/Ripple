cmake_minimum_required(VERSION 3.13)

### General settings ###
project(hello-world VERSION 1.0.0)
set(root_dir ${CMAKE_CURRENT_LIST_DIR}/../../..)

### Add source files ###
add_executable(${PROJECT_NAME}
  main.cpp
  ${root_dir}/radars/cpp/stub/main.cpp
  )

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

### Add include folders ###
include_directories(
  ${root_dir}/radar-api
  ${root_dir}/radars/cpp/stub
  ${root_dir}/platform
  )

target_compile_options(${PROJECT_NAME} PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
          -Wall -Werror -Wextra -pedantic -pedantic-errors>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)
