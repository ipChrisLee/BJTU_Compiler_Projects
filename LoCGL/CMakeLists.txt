cmake_minimum_required(VERSION 3.23)
project(LoCGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

add_compile_options(
		-g -Wall -Werror -Wextra
)

add_link_options(-lm -v)

add_library(
		LoCGL SHARED
		src/ll1_analyzer.cpp
		src/grammar.cpp
)
target_link_libraries(LoCGL moe)

