# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.13)
 
message("vcpkg root: $ENV{VCPKG_ROOT}")
 
set(VCPKG_DEFAULT_TRIPLET "x64-windows")

# set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE "C:/c++libs/vcpkg/scripts/buildsystems/vcpkg.cmake")


message("toolchain file: ${CMAKE_TOOLCHAIN_FILE}")


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(WIN32_LEAN_AND_MEAN True) # todo: only for msvc?

set(CMAKE_FIND_DEBUG_MODE 1)
 
add_compile_definitions(NOMINMAX)

project ("ttrpg")

find_package("EnTT")

enable_testing()

# Include sub-projects.
add_subdirectory ("ttrpg")

add_subdirectory ("ttrpgApp")

add_subdirectory ("test")
