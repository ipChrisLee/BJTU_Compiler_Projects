#include "demo_lex.hpp"
#include <iostream>
#include <string>
#include "lialex_runtime.hpp"


const char * program =
	"int a=3;\n"
	"int b=4;\n"
	"int c=a+b;\n"
	"if (c == a) {\n"
	"\tprint_int(c);\n"
	"}";


int main() {
	auto buffer = std::string(program);
	
	using Lexer = lialex_runtime::Lexer<Demo::TokenType>;
	auto lexer = Lexer{
		Demo::nodeType,
		Demo::edges,
		Demo::start,
		Demo::start,
	};
	auto tokens = lexer.gen(buffer);
	for (auto & token: tokens) {
		if (token.tokenType != Demo::TokenType::WS_Str &&
			token.tokenType != Demo::TokenType::Line_Comments) {
			std::cout << Demo::get_token_type_name(token.tokenType) << ": "
			          << token.content << std::endl;
		}
	}
	return 0;
};