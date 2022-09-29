cmake_minimum_required(VERSION 3.23)
project(LiaLEX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

add_compile_options(
		-g -Wall -Werror -Wextra -pthread
)

add_link_options(-lpthread -lm -v -pthread)

add_executable(
		LiaLEX
		main.cpp
		regex_analyze.cpp
		fa.cpp
)
target_link_libraries(LiaLEX moe)
