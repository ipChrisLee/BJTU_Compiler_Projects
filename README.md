这是[ipLee](https://github.com/ipChrisLee)为[BJTU](https://www.bjtu.edu.cn)的Compiler课写的大作业。包括：

* 词法分析器生成器LiaLEX（LiaLEX is another LEX）
	* 怎么润Demo：
	  ```shell
	  cd Compiler_Projects # 进入项目主目录
	  demo/demo_lialex/run_demo_lialex.sh
	  ```
	  
	* demo里各个文件的作用：
		* `B.lialex`：定义了B语言的词法。
		* `B.hpp`：lialex生成的头文件。
		* `main.cpp`：demo处理函数。
		
	* 处理流程：
	
	  1. 编译LiaLEX。
	
	  2. 使用LiaLEX，根据语法文件`B.lialex`生成B语言Lexer的头文件`B.hpp`。
	
	  3. 编译`main.cpp`，输入`src.B`，输出二元组文件`res.txt`，表示词法分析的结果。
	
	     `main.cpp`里include了`B.hpp`和`$proj_root/runtime_lib/lialex_runtime`两个文件。
	
* 基于LL(1)的递归下降的语法分析器生成器LiaPPG（LiaPPG is another Predictive LL1Parser Generator）
  
	* TBD.
	
* To be done.



本项目的文件架构：

```text
.
├── CMakeLists.txt      项目根CMake文件。
├── LICENSE.md          本项目的LICENSE。
├── LiaLEX              LiaLEX（LiaLEX is another LEX）项目根目录。
├── LiaPPG              LiaPPG（LiaPPG is another Predictive LL1Parser Generator）项目根目录。
├── LoCGL               LoCGL（Lots of Compiler Generator Libraries）项目根目录。
├── README.md           本文件。
├── demo                所有的demo项目都在此。
├── logs                日志文件夹，项目代码运行时的日志都存放在这。
├── moe                 引用的本人写的moe库用来方便C++编程。
├── runtime_lib         支持生成的Lexer、Parser跑起来的运行时库。
└── tools               一些项目中使用的工具。
```

欢迎您翻阅或者与我交流。