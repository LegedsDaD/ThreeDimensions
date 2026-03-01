cmake_minimum_required(VERSION 3.15)
project(ThreeDimensions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Optimization flags
if(MSVC)
    add_compile_options(/O2 /arch:AVX2 /fp:fast)
else()
    add_compile_options(-O3 -march=native -ffast-math -pthread)
endif()

# Fetch pybind11
include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        v2.11.1
)
FetchContent_MakeAvailable(pybind11)

# Include directories
include_directories(
    cpp_core/math
    cpp_core/geometry
    cpp_core/mesh
    cpp_core/topology
    cpp_core/modifiers
    cpp_core/sculpt
    cpp_core/curves
)

# Core library sources
file(GLOB_RECURSE SOURCES
    "cpp_core/math/*.cpp"
    "cpp_core/geometry/*.cpp"
    "cpp_core/mesh/*.cpp"
    "cpp_core/topology/*.cpp"
    "cpp_core/modifiers/*.cpp"
    "cpp_core/sculpt/*.cpp"
    "cpp_core/curves/*.cpp"
    "cpp_core/bindings.cpp"
)

# Create the python extension module
pybind11_add_module(_threedimensions_core ${SOURCES})

# Link libraries
target_link_libraries(_threedimensions_core PRIVATE pybind11::module)

# Install rules
install(TARGETS _threedimensions_core DESTINATION python/threedimensions)
