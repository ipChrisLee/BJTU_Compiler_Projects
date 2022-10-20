#pragma once

#include <map>
#include <string>
#include <vector>
#include <string_view>
#include "moe/log.hpp"
#include "moe/stl_pro.hpp"
#include "moe/moe_typedef.hpp"
#include "moe/debugger.hpp"

#include "grammar.hpp"


namespace ll1 {

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
	std::map<std::string, std::set<std::string>> follow;
	
	void analyze_epsilon_reachable();
	
	void get_first();
	
	void get_follow();
	
	void log_it(moe::LocalLog & lLog) override;
	
};

}
