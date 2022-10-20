cmake_minimum_required(VERSION 3.23)
project(Compiler_Projects)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

include_directories(./LiaLEX/lialex_runtime)
include_directories(./LoCGL/src)
include_directories(./moe)

add_subdirectory(moe)
add_subdirectory(./LiaLEX)
add_subdirectory(./LiaPPG)
add_subdirectory(./LoCGL)
