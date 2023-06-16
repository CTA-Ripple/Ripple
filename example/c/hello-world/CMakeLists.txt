cmake_minimum_required(VERSION 3.13)

### General settings ###
project(hello-world VERSION 1.0.0)
set(root_dir ${CMAKE_CURRENT_LIST_DIR}/../../..)

### Add source files ###
add_executable(${PROJECT_NAME}
  main.c
  ${root_dir}/radars/c/stub/main.c
  )

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)


### Add include folders ###
include_directories(
  ${root_dir}/radar-api
  ${root_dir}/radars/c/stub
  ${root_dir}/platform
  )

target_compile_options(${PROJECT_NAME} PRIVATE
     $<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:AppleClang>>:
          -Wall -Werror -Wextra -pedantic -pedantic-errors>
     $<$<C_COMPILER_ID:MSVC>:
          /W4>)
