#include <iostream>
#include <fstream>
#include <filesystem>
#include "LL1.hpp"
#include <arg_parser.hpp>
#include <log.hpp>


struct Info {
	std::string grammarFilePath;
	
	[[nodiscard]] bool legal() const {
		auto l = true;
		l |= std::filesystem::exists(grammarFilePath);
		return l;
	}
};

Info parse_command_line_args(int argc, char ** argv) {
	auto ppgInfo = Info();
	auto argParser = moe::ArgParser();
	argParser.add_option(
		moe::ArgOption(
			std::nullopt, "gra", true, [&ppgInfo](std::string_view sv) {
				ppgInfo.grammarFilePath = sv;
			}, "Grammar file path (i.e. Parser rules file path)."
		)
	);
	argParser.parse(argc, argv);
	return ppgInfo;
}

int main(int argc, char ** argv) {
	auto ppgInfo = parse_command_line_args(argc, argv);
	moe::register_std_log("logs/liappg/std_log.txt");
	
	auto analyzer = LL1::LL1Analyzer();
	analyzer.read(
		[&ppgInfo]() {
			auto ifs = std::ifstream(ppgInfo.grammarFilePath);
			auto lines = std::string();
			auto buffer = std::string();
			while (std::getline(ifs, buffer)) {
				lines += buffer;
			}
			return lines;
		}()
	);
	
	
	return 0;
}