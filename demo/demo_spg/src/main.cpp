#include <iostream>
#include <string>

#include <log.hpp>

#include <locgl_runtime.hpp>
#include <lialex_runtime.hpp>


#include "ll_lexer_info.hpp"
#include "ll_parser_info.hpp"


int main() {
	auto src = std::string();
	auto buf = std::string();
	while (std::getline(std::cin, buf)) {
		src += buf;
		src.push_back('\n');
	}
	
	auto lexer = lialex_runtime::Lexer<ll_lexer_info::TokenType>{
		ll_lexer_info::nodeType,
		ll_lexer_info::edges,
		ll_lexer_info::start,
		ll_lexer_info::start,
		ll_lexer_info::tokensToBeThrown,
	};
	auto lexerTokens = lexer.gen(src);
//	for (auto & token: lexerTokens) {
//		std::cerr << ll_lexer_info::get_token_type_name(token.tokenType) << ": "
//		          << token.content << std::endl;
//	}
	auto tokenFileStr = std::string();
	for (auto & lexerToken: lexerTokens) {
		tokenFileStr += lexerToken.print_to_parser(ll_lexer_info::get_token_type_name);
	}
//	std::cout << tokenFileStr << std::endl;
//	std::cout << "----------------------" << std::endl;
	auto parser = locgl_slr1_runtime::SLR1Parser<ll_parser_info::RuleType, ll_parser_info::ParseType>{
		ll_parser_info::actionTableR,
		ll_parser_info::actionTableS,
		ll_parser_info::actionTableG,
		ll_parser_info::start,
		ll_parser_info::end,
		ll_parser_info::startRule,
		ll_parser_info::endRule,
		ll_parser_info::theFirstParseType,
		ll_parser_info::parseTypeToRule,
		ll_parser_info::ruleTypeToStr,
		ll_parser_info::parseTypeToStr,
	};
	
	moe_assert(parser.is_legal());
	
	auto parserRules = parser.gen_from_str(tokenFileStr, ll_parser_info::strToRuleType);
//	for (auto & rule: parserRules) {
//		std::cout << rule.content << std::endl;
//	}
	auto pASTRoot = parser.parse_with_table(parserRules);
	std::cout << "digraph slr1_ast{" << std::endl;
	std::cout << pASTRoot->to_dot(ll_parser_info::ruleTypeToStr, ll_parser_info::parseTypeToStr)
	          << std::endl;
	std::cout << "}" << std::endl;
	
	return 0;
}