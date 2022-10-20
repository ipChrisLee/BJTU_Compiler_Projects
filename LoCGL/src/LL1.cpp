#include "LL1.hpp"


namespace gra {

void Gra::read_gra(std::string_view src) {
	auto preRule = std::string();
	auto lines = moe::split_string_on_char(src, "\n");
	for (auto & line: lines) {
//			moe_dbg(line);
		moe_slog_info(line);
		auto ruleItems = moe::split_string_on_char(line, " \t");
		auto ruleDef = std::vector<std::string>();
		auto idx = i32(-1);
		moe_assert(ruleItems.size() > 1, "There should be more than one item!");
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

}

namespace ll1 {
const std::string startStateName = "CompUnit";

const std::string epsilon = "$";


void LL1Analyzer::get_first() {
	analyze_epsilon_reachable();
	auto changed = false;
	auto vNonT = vocabulary;
	for (auto & x: vocabulary) {
		if (isTerm[x]) {
			first[x].insert(x);
			vNonT.erase(x);
		}
	}
	do {
		changed = false;
		for (auto & x: vNonT) {
			for (const auto & rule: allRules[x]) {
				auto beforeSZ = first[x].size();
				auto a = rule[0];
				if (isTerm[a] || a == epsilon) {
					first[x].insert(a);
				} else {    //  `a` is not terminator
					{
						auto tmp = first[a];
						tmp.erase(epsilon);
						first[x].insert(tmp.begin(), tmp.end());
					}
					auto allEpsilon = true;
					auto i = size_t(1);
					while (i < rule.size()) {
						allEpsilon &= bool(toEpsilon.count(rule[i]));
						if (!allEpsilon) {
							break;
						}
						auto tmp = first[rule[i]];
						tmp.erase(epsilon);
						++i;
					}
				}
				{
					auto epsilonInAllFirst = true;
					for (auto y: rule) {
						if (!first[y].count(epsilon)) {
							epsilonInAllFirst = false;
							break;
						}
					}
					if (epsilonInAllFirst) {
						first[x].insert(epsilon);
					}
				}
				auto afterSZ = first[x].size();
				changed |= (beforeSZ != afterSZ);
			}
		}
	} while (changed);
}

void LL1Analyzer::analyze_epsilon_reachable() {
	auto vis = std::map<std::string, bool>();
	auto st = std::stack<std::string>();
	st.push(epsilon);
	while (!st.empty()) {
		auto u = st.top();
		st.pop();
		if (vis[u]) { continue; }
		vis[u] = true;
		toEpsilon.insert(u);
		for (auto & rule: allRules) {
			auto & left = rule.first;
			for (auto & right: rule.second) {
				if (right.size() == 1 && right[0] == epsilon) {
					if (!vis[left]) {
						st.push(left);
					}
				}
			}
		}
	}
}

void LL1Analyzer::log_it(moe::LocalLog & lLog) {
	gra::Gra::log_it(lLog);
	{
		lLog.info("ToEpsilon:");
		moe_r_set(lLog.indent, lLog.indent + 1);
		for (auto & v: toEpsilon) {
			lLog.info(v);
		}
	}
	{
		lLog.info("First:");
		moe_r_set(lLog.indent, lLog.indent + 1);
		for (auto & x: vocabulary) {
			lLog.info(x);
			moe_r_set(lLog.indent, lLog.indent + 1);
			auto buf = std::string();
			for (auto & y: first[x]) {
				buf += y;
				buf += ' ';
			}
			lLog.info(buf);
		}
	}
}


}
