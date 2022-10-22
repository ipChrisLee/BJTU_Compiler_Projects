#include <iostream>
#include <fstream>
#include <filesystem>
#include <optional>

#include <arg_parser.hpp>
#include <decorator.hpp>
#include <log.hpp>
#include <ll1_analyzer.hpp>
#include <debugger.hpp>


struct Info {
	std::string grammarFilePath;
	std::string lexFilePath;
	std::optional<std::string> nameOfParser;
	std::string parserFilePathToGen;
	
	[[nodiscard]] bool legal() const {
		auto l = true;
		l |= std::filesystem::exists(grammarFilePath);
		l |= std::filesystem::exists(lexFilePath);
		l |= nameOfParser.has_value();
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
			}, "Grammar file path (i.e. LL1Parser rules file path)."
		)
	);
	argParser.add_option(
		moe::ArgOption(
			std::nullopt, "gra", true, [&ppgInfo](std::string_view sv) {
				ppgInfo.grammarFilePath = sv;
			}, "Lex file path (i.e. Lexer rules file path)."
		)
	);
	argParser.add_option(
		moe::ArgOption(
			std::nullopt, "name", true, [&ppgInfo](std::string_view sv) {
				ppgInfo.nameOfParser = sv;
			}, "Namespace of generated parser."
		)
	);
	argParser.add_option(
		moe::ArgOption(
			std::nullopt, "dest", true, [&ppgInfo](std::string_view sv) {
				ppgInfo.parserFilePathToGen = sv;
			}, "File path of generated parser."
		)
	);
	argParser.parse(argc, argv);
	return ppgInfo;
}

int main(int argc, char ** argv) {
	moe::register_std_log("logs/liappg/std_log.txt");
	
	auto ppgInfo = parse_command_line_args(argc, argv);
	
	//  print info of this generation.
	std::cout << moe::set_decorator(moe::Decorator::c_blue)
	          << "Generating `" << ppgInfo.nameOfParser.value()
	          << "` parser to \"" << ppgInfo.parserFilePathToGen
	          << "\" with lex defined in \"" << ppgInfo.lexFilePath << "\" "
	          << "and grammar defined in \"" << ppgInfo.grammarFilePath << "\"."
	          << moe::reset_decorator() << std::endl;
	
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
	analyzer.analyze();
	analyzer.log_it(analyzerLogger);
	analyzer
		.to_ll1_parser_info(ppgInfo.parserFilePathToGen, ppgInfo.nameOfParser.value());
	
	//  print info of this generation.
	std::cout << moe::set_decorator(moe::Decorator::c_green) << "Success!"
	          << moe::reset_decorator() << std::endl;
	return 0;
}