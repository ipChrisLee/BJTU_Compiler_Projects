cmake_minimum_required(VERSION 3.23)
project(LiaLEX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

add_compile_options(
		-g -Wall -Werror -Wextra
)

add_link_options(-lm -v)

add_executable(
		LiaLEX
		src/main.cpp
		src/regex_analyze.cpp
		src/fa.cpp
)
target_link_libraries(LiaLEX moe)
