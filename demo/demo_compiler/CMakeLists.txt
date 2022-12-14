cmake_minimum_required(VERSION 3.23)
project(demo_compiler)

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
		demo_compiler
		src/main.cpp
		src/frontend/typedef_for_b.cpp
		src/frontend/ast_visitor.cpp
		src/frontend/ast_visitor_for_block.cpp src/frontend/ast_visitor_for_decl.cpp)
target_link_libraries(demo_compiler moe)
target_link_libraries(demo_compiler LoCGL)
target_link_libraries(demo_compiler LiaIR)
