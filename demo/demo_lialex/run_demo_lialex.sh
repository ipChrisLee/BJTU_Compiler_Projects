# Run at root of project.
cmake_folder=cmake-build-debug
lialex_exe=${cmake_folder}/LiaLEX/LiaLEX

this_demo_path=demo/demo_lialex
lialex_file=${this_demo_path}/B.lialex
target_hpp=${this_demo_path}/B.hpp
lex_name=B
this_demo_main_cpp=${this_demo_path}/main.cpp
this_demo_main=${this_demo_path}/main
this_demo_src=${this_demo_path}/src.B
this_demo_res=${this_demo_path}/res.txt

mkdir -p "${cmake_folder}"
cmake -B "${cmake_folder}" -G "Unix Makefiles"
cd ${cmake_folder} && make LiaLEX && cd ..
${lialex_exe} --lex ${lialex_file} -o ${target_hpp} --name ${lex_name}
clang++ ${this_demo_main_cpp} -o ${this_demo_main} -std=c++17 &&
  ./${this_demo_main} <${this_demo_src} >${this_demo_res} &&
  rm ${this_demo_main}
