cmake_minimum_required(VERSION 3.23)
project(demo_ppg_hw)

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
		demo_ppg_hw
		src/main.cpp
)
target_link_libraries(demo_ppg_hw moe)
target_link_libraries(demo_ppg_hw LoCGL)
