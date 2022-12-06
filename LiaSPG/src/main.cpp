#include <string>
#include <optional>
#include <filesystem>

#include <moe/arg_parser.hpp>
#include <moe/stl_pro.hpp>
#include <moe/log.hpp>
#include <moe/rt_check.hpp>
#include <moe/decorator.hpp>

#include "slr1_analyzer.hpp"

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
	moe::register_std_log("logs/liaspg/std_log.txt");
	
	auto spgInfo = parse_command_line_args(argc, argv);
	moe_assert(spgInfo.legal());
	
	//  print info of this generation.
	std::cout << moe::set_decorator(moe::Decorator::c_blue)
	          << "Generating `" << spgInfo.nameOfParser.value()
	          << "` parser to \"" << spgInfo.parserFilePathToGen
	          << "\" with lex defined in \"" << spgInfo.lexFilePath << "\" "
	          << "and grammar defined in \"" << spgInfo.grammarFilePath << "\"."
	          << moe::reset_decorator() << std::endl;
	
	auto analyzer = slr1::SLR1Analyzer();
	analyzer.read_gra(
		[&spgInfo]() {
			auto ifs = std::ifstream(spgInfo.grammarFilePath);
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
		[&spgInfo]() {
			auto ifs = std::ifstream(spgInfo.lexFilePath);
			auto lines = std::string();
			auto buffer = std::string();
			while (std::getline(ifs, buffer)) {
				lines += buffer;
				lines += '\n';
			}
			return lines;
		}()
	);
	auto analyzerLogger = moe_llog("logs/liaspg/analyzer.txt", " ", true, "//");
	analyzer.analyze();
	analyzer.log_it(analyzerLogger);
	analyzer
		.to_slr1_parser_info(spgInfo.parserFilePathToGen, spgInfo.nameOfParser.value());
	
	//  print info of this generation.
	std::cout << moe::set_decorator(moe::Decorator::c_green) << "Success!"
	          << moe::reset_decorator() << std::endl;
	
	
	return 0;
}