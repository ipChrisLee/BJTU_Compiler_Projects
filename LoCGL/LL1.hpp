#pragma once

#include <map>
#include <string>
#include <vector>
#include <string_view>
#include <log.hpp>
#include <stl_pro.hpp>
#include <moe_typedef.hpp>


namespace LL1 {
/*
 * To simplify problems, rule only consists of 'concat' and 'or' operator.
 * So rule can be interpreted as std::map<std::string,std::vector<std::vector<std::string>>>
 * Source format :
 *  a -> b c d
 *    | e f g
 */
struct LL1Analyzer { //  LL(1) analyzer
	std::map<std::string, std::vector<std::vector<std::string>>> allRules;
	
	void read(std::string_view src) {
		auto preRule = std::string();
		auto lines = moe::split_string_on_char(preRule, "\n");
		for (auto & line: lines) {
			auto ruleItems = moe::split_string_on_char(line, " \t");
			auto ruleDef = std::vector<std::string>();
			auto idx = i32(-1);
			moe_assert(ruleItems.size() > 2, "There should be more than one item!");
			if (ruleItems[0] != "|") {  //  new rule
				preRule = ruleItems[0];
				moe_assert(ruleItems[1] == "->",
				           "For rule define line, \"->\" should exist.");
				idx = 2;
			} else {    //  continue
				idx = 1;
			}
			moe_assert(i32(ruleItems.size()) > idx, "Error!");
			for (; idx < i32(ruleItems.size()); ++idx) {
				ruleDef.emplace_back(ruleItems[idx]);
			}
			allRules[preRule].emplace_back(std::move(ruleDef));
		}
	}
	
};

}
