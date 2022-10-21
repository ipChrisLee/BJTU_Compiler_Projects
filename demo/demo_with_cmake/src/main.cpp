#include <iostream>
#include <string>


#include <locgl_runtime.hpp>
#include <lialex_runtime.hpp>
#include "LL_Lexer.hpp"


int main() {
	using namespace std::string_literals;
	auto src = "a=b + c"s;
	
	auto lexer = lialex_runtime::Lexer<ll_lex::TokenType>{
		ll_lex::nodeType,
		ll_lex::edges,
		ll_lex::start,
		ll_lex::start,
		ll_lex::tokensToBeThrown,
	};
	auto lexerTokens = lexer.gen(src);
	for (auto & token: lexerTokens) {
		std::cout << ll_lex::get_token_type_name(token.tokenType) << ": "
		          << token.content << std::endl;
	}
	auto tokenFileStr = std::string();
	for (auto & lexerToken: lexerTokens) {
		tokenFileStr += lexerToken.print_to_parser(ll_lex::get_token_type_name);
	}
	return 0;
}