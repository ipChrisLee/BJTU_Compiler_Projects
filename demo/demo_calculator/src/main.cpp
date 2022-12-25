#include <string>
#include <filesystem>
#include <fstream>

#include <lialex_runtime.hpp>
#include <locgl_runtime.hpp>

#include <moe/arg_parser.hpp>
#include <moe/rt_check.hpp>
#include <moe/stl_pro.hpp>

#include "b_lexer_info.hpp"
#include "b_parser_info.hpp"


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
	auto parser
		= locgl_slr1_runtime::SLR1Parser<b_parser_info::RuleType, b_parser_info::ParseType>{
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


using RuleType = b_parser_info::RuleType;
using ParseType = b_parser_info::ParseType;

using ASTNode = gast::ASTNodeWithInfo<RuleType, ParseType>;
using SPtrASTNode = std::shared_ptr<ASTNode>;

std::string vis_ast_node(const SPtrASTNode & pNode) {
	auto res = std::string();
	res += "{ content=\"" + pNode->content + "\", ";
	{
		res += "parseType=";
		if (pNode->parseType.has_value()) {
			res += b_parser_info::parseTypeToStr(pNode->parseType.value());
		} else {
			res += "None";
		}
		res += ", ";
	}
	{
		res += "ruleType=";
		res += b_parser_info::ruleTypeToStr(pNode->ruleType);
	}
	res += " }";
	return res;
}

u32 tmpCnt;
std::string res;

std::string quad_instr(std::string op, std::string srcL, std::string srcR, std::string dst) {
	return moe::concat_all("(", op, ", ", srcL, ", ", srcR, ", ", dst, ")\n");
}

std::string nxt_tmp() {
	++tmpCnt;
	return moe::concat_all("t", tmpCnt);
}

std::string visit_children(const SPtrASTNode & pNode);
std::string visit_stmt_assign(const SPtrASTNode & pNode);
std::string visit_l_val_var(const SPtrASTNode & pNode);
std::string visit_add_exp_add(const SPtrASTNode & pNode);
std::string visit_add_exp_sub(const SPtrASTNode & pNode);
std::string visit_mul_exp_mul(const SPtrASTNode & pNode);
std::string visit_mul_exp_div(const SPtrASTNode & pNode);
std::string visit_mul_exp_mod(const SPtrASTNode & pNode);
std::string visit_unary_exp_neg(const SPtrASTNode & pNode);
std::string visit_unary_exp_pos(const SPtrASTNode & pNode);
std::string visit_primary_exp_paren_exp(const SPtrASTNode & pNode);


std::string visit_dispatch(const SPtrASTNode & pNode) {
	std::cerr << vis_ast_node(pNode) << std::endl;
	if (pNode->parseType.has_value()) {
		switch (pNode->parseType.value()) {
			case ParseType::block_content_body:
			case ParseType::block_content_last:
			case ParseType::block_item_decl:
			case ParseType::comp_unit:
			case ParseType::const_exp:
			case ParseType::add_exp_flow:
			case ParseType::mul_exp_flow:
			case ParseType::unary_exp_flow:
			case ParseType::primary_exp_r_val:
			case ParseType::primary_exp_literal_int: {
				return visit_children(pNode);
			}
			case ParseType::stmt_assign: {
				return visit_stmt_assign(pNode);
			}
			case ParseType::l_val_var: {
				return visit_l_val_var(pNode);
			}
			case ParseType::add_exp_add: {
				return visit_add_exp_add(pNode);
			}
			case ParseType::add_exp_sub: {
				return visit_add_exp_sub(pNode);
			}
			case ParseType::mul_exp_mul: {
				return visit_mul_exp_mul(pNode);
			}
			case ParseType::mul_exp_div: {
				return visit_mul_exp_div(pNode);
			}
			case ParseType::mul_exp_mod: {
				return visit_mul_exp_mod(pNode);
			}
			case ParseType::unary_exp_neg: {
				return visit_unary_exp_neg(pNode);
			}
			case ParseType::unary_exp_pos: {
				return visit_unary_exp_pos(pNode);
			}
			case ParseType::primary_exp_paren_exp: {
				return visit_primary_exp_paren_exp(pNode);
			}
			default: {
				moe_rt_todo();
			}
		}
	} else {
		switch (pNode->ruleType) {
			case RuleType::literalInt:
			case RuleType::idName: {
				return pNode->content;
			}
			case RuleType::sepSemicolon: {
				return "";
			}
			default: {
				moe_rt_todo();
			}
		}
	}
}

std::string visit_children(const SPtrASTNode & pNode) {
	if (pNode->sons.size() == 1) {
		return visit_dispatch(pNode->sons[0]);
	}
	for (const auto & pSon: pNode->sons) {
		visit_dispatch(pSon);
	}
	return "";
}

std::string visit_l_val_var(const SPtrASTNode & pNode) {
	return visit_dispatch(pNode->sons[0]);
}

std::string visit_stmt_assign(const SPtrASTNode & pNode) {
	auto left = visit_dispatch(pNode->sons[0]);
	auto right = visit_dispatch(pNode->sons[2]);
	res += quad_instr("=", right, "", left);
	return res;
}

std::string visit_add_exp_add(const SPtrASTNode & pNode) {
	auto dst = nxt_tmp();
	auto srcL = visit_dispatch(pNode->sons[0]);
	auto srcR = visit_dispatch(pNode->sons[2]);
	res += quad_instr("+", srcL, srcR, dst);
	return dst;
}

std::string visit_add_exp_sub(const SPtrASTNode & pNode) {
	auto dst = nxt_tmp();
	auto srcL = visit_dispatch(pNode->sons[0]);
	auto srcR = visit_dispatch(pNode->sons[2]);
	res += quad_instr("-", srcL, srcR, dst);
	return dst;
}

std::string visit_mul_exp_mul(const SPtrASTNode & pNode) {
	auto dst = nxt_tmp();
	auto srcL = visit_dispatch(pNode->sons[0]);
	auto srcR = visit_dispatch(pNode->sons[2]);
	res += quad_instr("*", srcL, srcR, dst);
	return dst;
}

std::string visit_mul_exp_div(const SPtrASTNode & pNode) {
	auto dst = nxt_tmp();
	auto srcL = visit_dispatch(pNode->sons[0]);
	auto srcR = visit_dispatch(pNode->sons[2]);
	res += quad_instr("/", srcL, srcR, dst);
	return dst;
}

std::string visit_mul_exp_mod(const SPtrASTNode & pNode) {
	auto dst = nxt_tmp();
	auto srcL = visit_dispatch(pNode->sons[0]);
	auto srcR = visit_dispatch(pNode->sons[2]);
	res += quad_instr("%", srcL, srcR, dst);
	return dst;
}

std::string visit_unary_exp_neg(const SPtrASTNode & pNode) {
	auto dst = nxt_tmp();
	auto srcL = "0";
	auto srcR = visit_dispatch(pNode->sons[1]);
	res += quad_instr("-", srcL, srcR, dst);
	return dst;
}

std::string visit_unary_exp_pos(const SPtrASTNode & pNode) {
	auto dst = nxt_tmp();
	auto srcL = "0";
	auto srcR = visit_dispatch(pNode->sons[1]);
	res += quad_instr("+", srcL, srcR, dst);
	return dst;
}

std::string visit_primary_exp_paren_exp(const SPtrASTNode & pNode) {
	return visit_dispatch(pNode->sons[1]);
}

int main(int argc, char ** argv) {
	parse_info(argc, argv);
	auto pAst = generate_ast();
	visit_dispatch(pAst);
	{
		auto ofs = std::ofstream(info.dstFilePath.value());
		ofs << res << std::endl;
	}
	return 0;
}