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
# build lialex and liappg
cd ${cmake_folder} && make LiaLEX && cd ..
cd ${cmake_folder} && make LiaPPG && cd ..

lialex_exe=${cmake_folder}/LiaLEX/LiaLEX
liappg_exe=${cmake_folder}/LiaPPG/LiaPPG

this_demo_path=demo/demo_ppg

lialex_file=${this_demo_path}/LL.lialex
#lialex_file=${this_demo_path}/LL_with_literal.lialex
liappg_file=${this_demo_path}/LL.liagra
#liappg_file=${this_demo_path}/LL_with_literal.liagra
target_lexer_info_hpp=${this_demo_path}/src/ll_lexer_info.hpp
target_parser_info_hpp=${this_demo_path}/src/ll_parser_info.hpp
lexer_info_name=ll_lexer_info
parser_info_name=ll_parser_info

this_demo_exe=${cmake_folder}/demo/demo_ppg/demo_ppg
this_demo_src=${this_demo_path}/src.LL
this_demo_dst=${this_demo_path}/ast.dot

# generate lexer and parser info
${lialex_exe} --lex ${lialex_file} -o ${target_lexer_info_hpp} --name ${lexer_info_name}
${liappg_exe} --lex ${lialex_file} --gra ${liappg_file} --name ${parser_info_name} \
  --dest ${target_parser_info_hpp}

# make demo
cd ${cmake_folder} && make demo_ppg && cd ..

# run this demo. stdin is source file. stdout is dest file(a dot file represents ast).
${this_demo_exe} <${this_demo_src} >${this_demo_dst}
echo $?
