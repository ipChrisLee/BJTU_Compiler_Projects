#include <moe/stl_pro.hpp>

#include "grammar.hpp"


namespace gra {

void Gra::read_gra(std::string_view src) {
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
			ruleDef.emplace_back(ruleItems[idx]);
		}
		allRules[preRule].emplace_back(std::move(ruleDef));
		vocabulary.insert(preRule);
	}
}

void Gra::read_lex(std::string_view src) {
	auto lines = moe::split_string_on_char(src, "\n");
	for (auto & line: lines) {
//		moe_slog_info(line);
		auto ruleDef = moe::split_string_on_char(line, " \t\n");
		if (ruleDef[0] == "+") {
			isTerm[ruleDef[1]] = true;
			vocabulary.insert(ruleDef[1]);
		}
	}
}

void Gra::log_it(moe::LocalLog & lLog) {
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
				for (auto & item: right) {
					buf += item;
					buf.push_back(' ');
				}
				lLog.info(buf);
			}
		}
	}
}

const std::string startStateName = "CompUnit";

const std::string epsilon = "$";

const std::string endLabel = "#";

}

