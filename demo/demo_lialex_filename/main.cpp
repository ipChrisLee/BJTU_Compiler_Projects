#include <iostream>

#include <lialex_runtime.hpp>

#include "file_name.hpp"

int main() {
	auto srcProg = std::string();
	auto buffer = std::string();
	while (std::getline(std::cin, buffer)) {
		srcProg += buffer + "\n";
	}
	
	auto lexer = lialex_runtime::Lexer<file_name::TokenType>{
		file_name::nodeType,
		file_name::edges,
		file_name::start,
		file_name::start,
		file_name::tokensToBeThrown,
	};
	auto tokens = lexer.gen(srcProg);
	for (auto & token: tokens) {
		std::cout << file_name::get_token_type_name(token.tokenType) << ": "
		          << token.content << std::endl;
	}
}