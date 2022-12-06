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
  protected:
	std::set<std::string> toEpsilon;
	std::map<std::string, std::set<std::string>> first;
	std::map<std::string, std::set<std::string>> follow;
	
	void analyze_epsilon_reachable();
	
	std::set<std::string> first_of(const std::vector<std::string> & items);
	
	void get_first();
	
	void get_follow();
	
	
	std::map<
		std::string, std::map<std::string, std::pair<std::string, std::vector<std::string>>>
	> table;
	void get_table();
  
  public:
	void analyze();
	
	void log_it(moe::LocalLog & lLog) override;
	
	void to_ll1_parser_info(std::string_view filePath, std::string_view parserName);
	
};

}
