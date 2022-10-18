cmake_minimum_required(VERSION 3.23)
project(Compiler_Projects)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

include_directories(./LiaLEX/lialex_runtime)

add_subdirectory(moe)
include_directories(./moe)
add_subdirectory(LiaLEX)

add_compile_options(
		-g -Wall -Werror -Wextra
)

add_link_options(-lm -v)

add_executable(Compiler_Projects main.cpp)
target_link_libraries(Compiler_Projects moe)
