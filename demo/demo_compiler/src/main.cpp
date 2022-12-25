#include <string>
#include <filesystem>
#include <fstream>

#include <lialex_runtime.hpp>
#include <locgl_runtime.hpp>

#include <moe/arg_parser.hpp>
#include <moe/rt_check.hpp>

#include "frontend/b_lexer_info.hpp"
#include "frontend/b_parser_info.hpp"
#include "frontend/ast_visitor.hpp"


struct Info {
	std::optional<std::string> srcFilePath;
	std::optional<std::string> dstFilePath;
	std::optional<std::string> astDotFilePath;
	std::optional<std::string> lexerTokenFilePath;
	std::optional<std::string> parserTokenFilePath;
	
	[[nodiscard]] bool legal() const {
		auto hasValueAndExists = [](const std::optional<std::string> & s) {
			if (!s.has_value()) {
				return false;
			}
			return std::filesystem::exists(s.value());
		};
		auto res = true;
		res &= hasValueAndExists(srcFilePath);
		res &= dstFilePath.has_value();
		return res;
	}
} info;

void parse_info(int argc, char ** argv) {
	auto argParser = moe::ArgParser("B-Compiler");
	argParser.add_option(
		moe::ArgOption(
			std::nullopt, "src", true, [](std::string_view s) {
				info.srcFilePath = s;
			}, ""
		)
	);
	argParser.add_option(
		moe::ArgOption(
			'o', std::nullopt, true, [](std::string_view s) {
				info.dstFilePath = s;
			}, ""
		)
	);
	argParser.add_option(
		moe::ArgOption(
			std::nullopt, "ast-dot", true, [](std::string_view s) {
				info.astDotFilePath = s;
			}, ""
		)
	);
	argParser.add_option(
		moe::ArgOption(
			std::nullopt, "lexer-token", true, [](std::string_view s) {
				info.lexerTokenFilePath = s;
			}, ""
		)
	);
	argParser.add_option(
		moe::ArgOption(
			std::nullopt, "parser-token", true, [](std::string_view s) {
				info.parserTokenFilePath = s;
			}, ""
		)
	);
	argParser.parse(argc, argv);
	moe_assert(info.legal());
}

std::shared_ptr<gast::ASTNodeWithInfo<b_parser_info::RuleType, b_parser_info::ParseType>>
generate_ast() {
	auto src = std::string();
	auto buf = std::string();
	auto srcFileStream = std::ifstream(info.srcFilePath.value());
	while (std::getline(srcFileStream, buf)) {
		src += buf;
		src.push_back('\n');
	}
	
	auto lexer = lialex_runtime::Lexer<b_lexer_info::TokenType>{
		b_lexer_info::nodeType,
		b_lexer_info::edges,
		b_lexer_info::start,
		b_lexer_info::start,
		b_lexer_info::tokensToBeThrown,
	};
	auto lexerTokens = lexer.gen(src);
	if (info.lexerTokenFilePath.has_value()) {
		auto ofs = std::ofstream(info.lexerTokenFilePath.value());
		for (auto & token: lexerTokens) {
			ofs << b_lexer_info::get_token_type_name(token.tokenType) << ": "
			    << token.content << std::endl;
		}
	}
	auto tokenFileStr = std::string();
	for (auto & lexerToken: lexerTokens) {
		tokenFileStr += lexerToken.print_to_parser(b_lexer_info::get_token_type_name);
	}
//	std::cout << tokenFileStr << std::endl;
//	std::cout << "----------------------" << std::endl;
	auto parser = locgl_slr1_runtime::SLR1Parser<b_parser_info::RuleType, b_parser_info::ParseType>{
		b_parser_info::actionTableR,
		b_parser_info::actionTableS,
		b_parser_info::actionTableG,
		b_parser_info::start,
		b_parser_info::end,
		b_parser_info::startRule,
		b_parser_info::endRule,
		b_parser_info::theFirstParseType,
		b_parser_info::parseTypeToRule,
		b_parser_info::ruleTypeToStr,
		b_parser_info::parseTypeToStr,
	};
	moe_assert(parser.is_legal());
	
	auto parserRules = parser.gen_from_str(tokenFileStr, b_parser_info::strToRuleType);
	if (info.parserTokenFilePath.has_value()) {
		auto ofs = std::ofstream(info.parserTokenFilePath.value());
		for (auto & rule: parserRules) {
			ofs << rule.content << std::endl;
		}
	}
	auto pASTRoot = parser.parse_with_table(parserRules);
	if (info.astDotFilePath.has_value()) {
		auto ofs = std::ofstream(info.astDotFilePath.value());
		ofs << "digraph slr1_ast{" << std::endl;
		ofs << pASTRoot->to_dot(b_parser_info::ruleTypeToStr, b_parser_info::parseTypeToStr)
		    << std::endl;
		ofs << "}" << std::endl;
	}
	return pASTRoot;
}

int main(int argc, char ** argv) {
	parse_info(argc, argv);
	auto pAst = generate_ast();
	b_lan::visit_dispatch(pAst);
	return 0;
}