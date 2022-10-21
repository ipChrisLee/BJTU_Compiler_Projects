#include "B.hpp"
#include "../../runtime_lib/lialex_runtime.hpp"
#include <string>
#include <iostream>


int main() {
	auto srcProg = std::string();
	auto buffer = std::string();
	while (std::getline(std::cin, buffer)) {
		srcProg += buffer;
	}
	
	auto lexer = lialex_runtime::Lexer<B::TokenType>{
		B::nodeType,
		B::edges,
		B::start,
		B::start,
		B::tokensToBeThrown,
	};
	auto tokens = lexer.gen(srcProg);
	for (auto & token: tokens) {
		std::cout << B::get_token_type_name(token.tokenType) << ": "
		          << token.content << std::endl;
	}
	return 0;
}
