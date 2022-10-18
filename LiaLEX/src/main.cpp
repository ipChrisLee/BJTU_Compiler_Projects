#include "moe/decorator.hpp"
#include "moe/arg_parser.hpp"
#include "moe/moe_typedef.hpp"
#include "moe/log.hpp"
#include <iostream>
#include <string>
#include <variant>
#include "regex_analyze.hpp"
#include "fa.hpp"


int main(int argc, char ** argv) {
	auto lexFilePath = std::string();
	auto outFilePath = std::string();
	auto lexName = std::string();
	auto argParser = moe::ArgParser();
	argParser.add_option(
		moe::ArgOption(
			std::nullopt, "name", true, [&lexName](std::string_view s) {
				lexName = s;
			}, std::nullopt
		)
	);
	argParser.add_option(
		moe::ArgOption(
			std::nullopt, "lex", true, [&lexFilePath](std::string_view s) {
				lexFilePath = s;
			}, std::nullopt
		)
	);
	argParser.add_option(
		moe::ArgOption(
			'o', std::nullopt, true, [&outFilePath](std::string_view s) {
				outFilePath = s;
			}, std::nullopt
		)
	);
	argParser.parse(argc, argv);
	
	//  print info of this generation.
	std::cout << moe::set_decorator(moe::Decorator::c_blue)
	          << "Generating `" << lexName
	          << "` lexer to \"" << outFilePath
	          << "\" with lex defined in \"" << lexFilePath << "\"."
	          << moe::reset_decorator() << std::endl;
	
	using namespace LiaLEX;
	moe::register_std_log("logs/std_log.txt");
	moe_slog_info(lexFilePath);
	auto ruleAndRegexAST = scan_tex_rules(lexFilePath);
	auto rules = [&ruleAndRegexAST]() {
		auto r = std::vector<Rule>();
		for (auto & p: ruleAndRegexAST) {
			r.emplace_back(p.first);
		}
		return r;
	}();
	auto nfa = merge_all(ruleAndRegexAST);
	auto dfa = nfa2dfa(nfa);
	genHppBasingOnLex(dfa, outFilePath, lexName, rules);
	
	//  print info of this generation.
	std::cout << moe::set_decorator(moe::Decorator::c_green) << "Success!"
	          << moe::reset_decorator() << std::endl;
	return 0;
}
