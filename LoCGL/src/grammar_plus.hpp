#pragma once


#include <set>
#include <map>
#include <string>

#include <moe/log.hpp>

namespace gra { //  grammar

struct GraP {
	std::set<std::string> vocabulary;
	std::map<std::string, bool> isTerm; //  is terminator. endLabel is not terminator!
	std::map<std::string, std::map<std::string, std::vector<std::string>>> allRules;
	//  allRules[A][B][C] : A -> C % B
	std::map<std::pair<std::string, std::vector<std::string>>, std::string> ruleToName;
	//  ruleDef[A][C] : A.first -> A.second % C
	
	void read_gra(std::string_view src);
	
	void read_lex(std::string_view src);
	
	virtual void log_it(moe::LocalLog & lLog);
};

extern const std::string startStateName;

extern const std::string epsilon;

extern const std::string endLabel;

extern const std::string dot;

}
