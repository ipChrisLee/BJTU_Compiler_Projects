cmake_minimum_required(VERSION 3.23)
project(demo_with_cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

add_compile_options(
		-g
		-Wall
		-Wno-unused-function
		-Werror -Wextra
)

add_link_options(-lm -v)

add_executable(
		demo_with_cmake
		src/main.cpp
)
target_link_libraries(demo_with_cmake moe)
target_link_libraries(demo_with_cmake LoCGL)
