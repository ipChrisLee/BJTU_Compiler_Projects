cmake_minimum_required(VERSION 3.23)
project(Compiler_Projects)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

add_subdirectory(moe)

include_directories(./runtime_lib)
include_directories(./LoCGL/src)
include_directories(./LiaIR)
include_directories(./moe)

add_subdirectory(./LiaLEX)
add_subdirectory(./LiaPPG)
add_subdirectory(./LiaSPG)
add_subdirectory(./LoCGL)
add_subdirectory(./LiaIR)
add_subdirectory(./LC)
add_subdirectory(demo/demo_lialex_filename)
add_subdirectory(demo/demo_ppg)
add_subdirectory(demo/demo_spg)
