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

this_demo_path=demo/demo_calculator

lialex_file=${this_demo_path}/B.lialex
liaspg_file=${this_demo_path}/B.liagra
target_lexer_info_hpp=${this_demo_path}/src/b_lexer_info.hpp
target_parser_info_hpp=${this_demo_path}/src/b_parser_info.hpp
lexer_info_name=b_lexer_info
parser_info_name=b_parser_info

this_demo_exe=${cmake_folder}/demo/demo_calculator/demo_calculator
this_demo_src=${this_demo_path}/B/src.B
this_demo_dst=${this_demo_path}/B/dst.txt
this_demo_lexer_token=${this_demo_path}/B/lexer_token.txt
this_demo_parser_token=${this_demo_path}/B/parser_token.txt
this_demo_ast_dot=${this_demo_path}/B/ast.dot

# generate lexer and parser info
${lialex_exe} --lex ${lialex_file} -o ${target_lexer_info_hpp} --name ${lexer_info_name}
${liaspg_exe} --lex ${lialex_file} --gra ${liaspg_file} --name ${parser_info_name} \
  --dest ${target_parser_info_hpp}

# make demo
cd ${cmake_folder} && make demo_calculator && cd ..

# run this demo.
${this_demo_exe} \
  --src ${this_demo_src} \
  -o ${this_demo_dst} \
  --ast-dot ${this_demo_ast_dot} \
  --lexer-token ${this_demo_lexer_token} \
  --parser-token ${this_demo_parser_token}
echo $?
