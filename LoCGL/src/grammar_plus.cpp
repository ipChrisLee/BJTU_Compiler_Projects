#include "grammar_plus.hpp"

#include <moe/stl_pro.hpp>

namespace gra {

void GraP::read_gra(std::string_view src) {
	auto preRule = std::string();
	auto lines = moe::split_string_on_char(src, "\n");
	for (auto & line: lines) {
//			moe_dbg(line);
//		moe_slog_info(line);
		auto ruleItems = moe::split_string_on_char(line, " \t");
		auto ruleDef = std::vector<std::string>();
		auto idx = i32(-1);
		moe_assert(ruleItems.size() > 1, "There should be more than one item!");
		if (ruleItems[0] != "|") {  //  new rule
			preRule = ruleItems[0];
			moe_assert(
				ruleItems[1] == "->",
				"For rule define line, \"->\" should exist."
			);
			idx = 2;
		} else {    //  continue
			idx = 1;
		}
		moe_assert(i32(ruleItems.size()) > idx, "Error!");
		for (; idx < i32(ruleItems.size()); ++idx) {
			if (ruleItems[idx] == "%") {
				break;
			}
			ruleDef.emplace_back(ruleItems[idx]);
		}
		moe_assert(ruleItems[idx] == "%");
		moe_assert(i32(ruleItems.size()) == idx + 2);
		auto parseRuleName = ruleItems[idx + 1];
		allRules[preRule].emplace(std::make_pair(parseRuleName, ruleDef));
		ruleToName[std::make_pair(preRule, ruleDef)] = parseRuleName;
		vocabulary.insert(preRule);
	}
}

void GraP::read_lex(std::string_view src) {
	auto lines = moe::split_string_on_char(src, "\n");
	for (auto & line: lines) {
//		moe_slog_info(line);
		auto ruleDef = moe::split_string_on_char(line, " \t\n");
		if (ruleDef[0] == "+") {
			isTerm[ruleDef[1]] = true;
			vocabulary.insert(ruleDef[1]);
		}
	}
	moe_assert(allRules[startStateName].size() == 1);
}

void GraP::log_it(moe::LocalLog & lLog) {
	{
		lLog.info("Vocabulary:");
		moe_r_set(lLog.indent, lLog.indent + 1);
		for (auto & v: vocabulary) {
			lLog.info(v, (isTerm[v] ? "Vt" : "Vn"));
		}
	}
	{
		lLog.info("Rules:");
		moe_r_set(lLog.indent, lLog.indent + 1);
		for (auto & rule: allRules) {
			auto & left = rule.first;
			lLog.info(left, "->");
			moe_r_set(lLog.indent, lLog.indent + 1);
			for (auto & right: rule.second) {
				auto buf = std::string();
				for (auto & item: right.second) {
					buf += item;
					buf.push_back(' ');
				}
				buf += "% ";
				buf += right.first;
				lLog.info(buf);
			}
		}
	}
}

}
