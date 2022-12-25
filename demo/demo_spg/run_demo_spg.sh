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
cd ${cmake_folder} && make LiaSPG && cd ..

lialex_exe=${cmake_folder}/LiaLEX/LiaLEX
liaspg_exe=${cmake_folder}/LiaSPG/LiaSPG

this_demo_path=demo/demo_spg

lialex_file=${this_demo_path}/LL.lialex
#lialex_file=${this_demo_path}/ifelse.lialex
liaspg_file=${this_demo_path}/LL.liagra
#liaspg_file=${this_demo_path}/ifelse.liagra
target_lexer_info_hpp=${this_demo_path}/src/ll_lexer_info.hpp
target_parser_info_hpp=${this_demo_path}/src/ll_parser_info.hpp
lexer_info_name=ll_lexer_info
parser_info_name=ll_parser_info

this_demo_exe=${cmake_folder}/demo/demo_spg/demo_spg
this_demo_src=${this_demo_path}/src.LL
this_demo_dst=${this_demo_path}/ast.dot

# generate lexer and parser info
${lialex_exe} --lex ${lialex_file} -o ${target_lexer_info_hpp} --name ${lexer_info_name}
${liaspg_exe} --lex ${lialex_file} --gra ${liaspg_file} --name ${parser_info_name} \
  --dest ${target_parser_info_hpp}

# make demo
cd ${cmake_folder} && make demo_spg && cd ..

# run this demo. stdin is source file. stdout is dest file(a dot file represents ast).
${this_demo_exe} <${this_demo_src} >${this_demo_dst}
echo $?
