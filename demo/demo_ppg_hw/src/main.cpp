#include <iostream>

#include <lialex_runtime.hpp>
#include <locgl_runtime.hpp>

#include "hw_lexer_info.hpp"
#include "hw_parser_info.hpp"

int main() {
	auto src = std::string();
	auto buf = std::string();
	while (std::getline(std::cin, buf)) {
		src += buf;
		src.push_back('\n');
	}
	
	auto lexer = lialex_runtime::Lexer<hw_lexer_info::TokenType>{
		hw_lexer_info::nodeType,
		hw_lexer_info::edges,
		hw_lexer_info::start,
		hw_lexer_info::start,
		hw_lexer_info::tokensToBeThrown,
	};
	auto lexerTokens = lexer.gen(src);
//	for (auto & token: lexerTokens) {
//		std::cerr << ll_lexer_info::get_token_type_name(token.tokenType) << ": "
//		          << token.content << std::endl;
//	}
	auto tokenFileStr = std::string();
	for (auto & lexerToken: lexerTokens) {
		tokenFileStr += lexerToken.print_to_parser(hw_lexer_info::get_token_type_name);
	}
//	std::cout << tokenFileStr << std::endl;
//	std::cout << "----------------------" << std::endl;
	auto parser = locgl_ll1_runtime::LL1Parser<hw_parser_info::RuleType>{
		hw_parser_info::allRules,
		hw_parser_info::first,
		hw_parser_info::follow,
		hw_parser_info::terms,
		hw_parser_info::start,
		hw_parser_info::end,
		hw_parser_info::epsilon,
		hw_parser_info::table,
		hw_parser_info::ruleTypeToStr,
	};
//	{
//		auto tmp = parser.first_of({hw_parser_info::RuleType(7)});
//		std::for_each(
//			tmp.begin(), tmp.end(),
//			[](auto x) {
//				std::cout << int(x) << std::endl;
//			}
//		);
//	}
	auto parserRules = parser.gen_from_str(tokenFileStr, hw_parser_info::strToRuleType);
//	for (auto & rule: parserRules) {
//		std::cout << rule.content << std::endl;
//	}

//	auto pASTRoot = parser.parse_with_pp(parserRules);
//	std::cout << "digraph ast{" << std::endl;
//	std::cout << pASTRoot->to_dot(hw_parser_info::ruleTypeToStr) << std::endl;
//	std::cout << "}" << std::endl;
	
	auto pASTRoot = parser.parse_with_table(parserRules);
	std::cout << "digraph ast{" << std::endl;
	std::cout << pASTRoot->to_dot(hw_parser_info::ruleTypeToStr) << std::endl;
	std::cout << "}" << std::endl;
	
	return 0;
}