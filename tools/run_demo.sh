mkdir build
cmake -B build
cd build && make LiaLEX && cd ..
build/LiaLEX/LiaLEX --lex demo/demo.lialex -o demo/demo_lex.hpp --name Demo
cd build/demo && make && cd ../..
build/demo/demo <demo/demo_source_language.txt
