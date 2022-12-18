# Run at root of project.
root_judgement=$(sed -n '2p' CMakeLists.txt)
if [ "${root_judgement}" != "project(Compiler_Projects)" ]; then
  echo "Judgement finds that second line of ${PWD} is not \"project(Compiler_Projects)\", check if you are running this script on the project root."
  exit 1
fi

cmake_folder=cmake-build-debug
# cmake
mkdir -p "${cmake_folder}"
cmake -B "${cmake_folder}" -G "Unix Makefiles"
# build lialex and liaspg
cd ${cmake_folder} && make LiaLEX && cd ..

lialex_exe=${cmake_folder}/LiaLEX/LiaLEX

this_demo_path=demo/demo_lialex_filename

lialex_file=${this_demo_path}/file_name.lialex
target_lexer_info_hpp=${this_demo_path}/file_name.hpp
lexer_info_name=file_name

this_demo_exe=${cmake_folder}/demo/demo_lialex_filename/demo_lialex_filename
this_demo_src=${this_demo_path}/src.txt
this_demo_dst=${this_demo_path}/dst.txt

# generate lexer and parser info
${lialex_exe} --lex ${lialex_file} -o ${target_lexer_info_hpp} --name ${lexer_info_name}

# make demo
cd ${cmake_folder} && make demo_lialex_filename && cd ..

# run this demo. stdin is source file. stdout is dest file(a dot file represents ast).
${this_demo_exe} <${this_demo_src} >${this_demo_dst}
echo $?
