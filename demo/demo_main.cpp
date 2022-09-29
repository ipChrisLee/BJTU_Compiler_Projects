#include "demo_lex.hpp"
#include <iostream>
#include <string>
#include "lialex_runtime.hpp"


int main() {
	auto srcProg = std::string();
	auto buffer = std::string();
	while (std::getline(std::cin, buffer)) {
		srcProg += buffer;
	}
	
	using Lexer = lialex_runtime::Lexer<Demo::TokenType>;
	auto lexer = Lexer{
		Demo::nodeType,
		Demo::edges,
		Demo::start,
		Demo::start,
	};
	auto tokens = lexer.gen(srcProg);
	for (auto & token: tokens) {
		if (token.tokenType != Demo::TokenType::WS_Str &&
			token.tokenType != Demo::TokenType::Line_Comments &&
			token.tokenType != Demo::TokenType::M_Line_Comments) {
			std::cout << Demo::get_token_type_name(token.tokenType) << ": "
			          << token.content << std::endl;
		}
	}
	return 0;
};