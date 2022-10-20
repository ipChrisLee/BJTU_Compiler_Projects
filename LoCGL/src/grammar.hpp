#pragma once

#include <set>
#include <string>
#include <map>
#include <vector>

#include <moe/log.hpp>


namespace gra { //  grammar

struct Gra {
	std::set<std::string> vocabulary;
	std::map<std::string, bool> isTerm; //  is terminator
	std::map<std::string, std::vector<std::vector<std::string>>> allRules;
	
	void read_gra(std::string_view src);
	
	void read_lex(std::string_view src);
	
	virtual void log_it(moe::LocalLog & lLog);
};

extern const std::string startStateName;

extern const std::string epsilon;

extern const std::string endLabel;

}

