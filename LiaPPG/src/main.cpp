#include <iostream>
#include <fstream>
#include <filesystem>
#include <arg_parser.hpp>
#include <log.hpp>
#include <ll1_analyzer.hpp>
#include <debugger.hpp>


struct Info {
	std::string grammarFilePath;
	std::string lexFilePath;
	
	[[nodiscard]] bool legal() const {
		auto l = true;
		l |= std::filesystem::exists(grammarFilePath);
		l |= std::filesystem::exists(lexFilePath);
		return l;
	}
};

Info parse_command_line_args(int argc, char ** argv) {
	auto ppgInfo = Info();
	auto argParser = moe::ArgParser();
	argParser.add_option(
		moe::ArgOption(
			std::nullopt, "lex", true, [&ppgInfo](std::string_view sv) {
				ppgInfo.lexFilePath = sv;
			}, "Grammar file path (i.e. Parser rules file path)."
		)
	);
	argParser.add_option(
		moe::ArgOption(
			std::nullopt, "gra", true, [&ppgInfo](std::string_view sv) {
				ppgInfo.grammarFilePath = sv;
			}, "Lex file path (i.e. Lexer rules file path)."
		)
	);
	argParser.parse(argc, argv);
	return ppgInfo;
}

int main(int argc, char ** argv) {
	moe::register_std_log("logs/liappg/std_log.txt");
	
	auto ppgInfo = parse_command_line_args(argc, argv);
	
	auto analyzer = ll1::LL1Analyzer();
	analyzer.read_gra(
		[&ppgInfo]() {
			auto ifs = std::ifstream(ppgInfo.grammarFilePath);
			auto lines = std::string();
			auto buffer = std::string();
			while (std::getline(ifs, buffer)) {
				lines += buffer;
				lines += '\n';
			}
			return lines;
		}()
	);
	analyzer.read_lex(
		[&ppgInfo]() {
			auto ifs = std::ifstream(ppgInfo.lexFilePath);
			auto lines = std::string();
			auto buffer = std::string();
			while (std::getline(ifs, buffer)) {
				lines += buffer;
				lines += '\n';
			}
			return lines;
		}()
	);
	auto analyzerLogger = moe_llog("logs/liappg/analyzer.txt", " ", true, "//");
	analyzer.get_first();
	analyzer.get_follow();
	analyzer.log_it(analyzerLogger);
	
	
	return 0;
}