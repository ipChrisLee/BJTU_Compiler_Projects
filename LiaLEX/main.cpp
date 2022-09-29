#include <moe/decorator.hpp>
#include <moe/arg_parser.hpp>
#include <moe/moe_typedef.hpp>
#include <moe/log.hpp>
#include <iostream>
#include <string>
#include <variant>
#include "regex_analyze.hpp"
#include "fa.hpp"


int main(int argc, char ** argv) {
	moe::register_std_log("logs/std_log.txt");
	
	auto lexFilePath = std::string();
	auto outFilePath = std::string();
	auto lexName = std::string();
	auto argParser = moe::ArgParser();
	argParser.emplace_option(
		0, "name", true, [&lexName](const char * s) {
			lexName = s;
		}
	);
	argParser.emplace_option(
		0, "lex", true, [&lexFilePath](const char * s) {
			lexFilePath = s;
		}
	);
	argParser.emplace_option(
		'o', nullptr, true, [&outFilePath](const char * s) {
			outFilePath = s;
		}
	);
	argParser.parse(argc, argv);
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
	return 0;
}