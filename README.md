这是[ipLee](https://github.com/ipChrisLee)为[BJTU](https://www.bjtu.edu.cn)的Compiler课写的大作业。包括：

* 词法分析器生成器LiaLEX（LiaLEX Is Another LEX）
  * 怎么润一个Demo：
  
    ```shell
    cd Compiler_Projects
    cmake -B build
    cd build
    make LiaLEX
    cd ..
    build/LiaLEX/LiaLEX --lex demo/demo.lialex -o demo/demo_lex.hpp --name Demo
    cd build/demo
    make
    cd ../..
    build/demo/demo < demo/demo_source_language.txt
    ```
  
  * 各个文件的作用：
  
    * `demo/demo.lialex`：定义了demo语言的词法。
    * `demo/demo_lex.hpp`：输出规则到。
    * `demo/demo_main.cpp`：demo的main函数。
    * `demo/demo_source_language.txt`：需要被编译的源语言。基本是C的子集。
  
* To be done.

欢迎您翻阅。