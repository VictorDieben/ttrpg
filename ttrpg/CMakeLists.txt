

cmake_minimum_required (VERSION 3.13)


# message("TtrpgLib source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(TtrpgLib
    "include/ttrpg/ttrpg.h" 
    "include/ttrpg/definitions_dnd.h"
    "src/ttrpg/ttrpg.cpp"  "include/ttrpg/definitions.h")

target_include_directories(TtrpgLib
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include 
)

target_link_libraries(TtrpgLib PUBLIC EnTT::EnTT)

target_compile_features(TtrpgLib PUBLIC cxx_std_20)

add_library(${PROJECT_NAMESPACE}::TtrpgLib ALIAS TtrpgLib )
