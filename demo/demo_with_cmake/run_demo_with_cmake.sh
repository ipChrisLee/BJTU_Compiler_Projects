# Run at root of project.
root_judgement=$(sed -n '2p' CMakeLists.txt)
if [ "${root_judgement}" != "project(Compiler_Projects)" ]; then
  echo "Judgement finds that second line of ${PWD} is not \"project(Compiler_Projects)\", check if you are running this script on the project root."
  exit 1
fi

cmake_folder=cmake-build-debug
lialex_exe=${cmake_folder}/LiaLEX/LiaLEX

this_demo_path=demo/demo_with_cmake

lialex_file=${this_demo_path}/LL.lialex
target_lialex_hpp=${this_demo_path}/src/LL_Lexer.hpp
lex_name=ll_lex

${lialex_exe} --lex ${lialex_file} -o ${target_lialex_hpp} --name ${lex_name}
