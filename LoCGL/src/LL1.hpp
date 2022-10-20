#pragma once

#include <map>
#include <string>
#include <vector>
#include <string_view>
#include "moe/log.hpp"
#include "moe/stl_pro.hpp"
#include "moe/moe_typedef.hpp"
#include "moe/debugger.hpp"


namespace gra { //  grammar

struct Gra {
	std::set<std::string> vocabulary;
	std::map<std::string, bool> isTerm; //  is terminator
	std::map<std::string, std::vector<std::vector<std::string>>> allRules;
	
	void read_gra(std::string_view src);
	
	void read_lex(std::string_view src);
	
	virtual void log_it(moe::LocalLog & lLog);
};
}

namespace ll1 {

extern const std::string startStateName;

extern const std::string epsilon;

/*
 * To simplify problems, rule only consists of 'concat' and 'or' operator.
 * So rule can be interpreted as std::map<std::string,std::vector<std::vector<std::string>>>
 * Source format :
 *  a -> b c d
 *    | e f g
 */
struct LL1Analyzer : gra::Gra { //  LL(1) analyzer
	std::set<std::string> toEpsilon;
	std::map<std::string, std::set<std::string>> first;
	
	void analyze_epsilon_reachable();
	
	void get_first();
	
	void log_it(moe::LocalLog & lLog) override;
	
};

}
