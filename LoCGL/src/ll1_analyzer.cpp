#include "ll1_analyzer.hpp"


namespace ll1 {

void LL1Analyzer::get_first() {
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
				if (isTerm[a] || a == gra::epsilon) {
					first[x].insert(a);
				} else {    //  `a` is not terminator
					{
						auto tmp = first[a];
						tmp.erase(gra::epsilon);
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
						tmp.erase(gra::epsilon);
						++i;
					}
				}
				{
					auto epsilonInAllFirst = true;
					for (auto y: rule) {
						if (!first[y].count(gra::epsilon)) {
							epsilonInAllFirst = false;
							break;
						}
					}
					if (epsilonInAllFirst) {
						first[x].insert(gra::epsilon);
					}
				}
				auto afterSZ = first[x].size();
				changed |= (beforeSZ != afterSZ);
			}
		}
	} while (changed);
}

void LL1Analyzer::get_follow() {
	moe_assert(vocabulary.count(gra::startStateName), "`CompUnit` not found!");
	follow[gra::startStateName].insert(gra::endLabel);
	auto changed = false;
	do {
		changed = false;
		for (auto & rule: allRules) {
			auto & A = rule.first;
//			moe_slog_info(A);
			for (auto & right: rule.second) {
				for (auto i = size_t(0); i < right.size(); ++i) {
					auto & B = right[i];
					auto beforeSZ = follow[B].size();
					if (i + 1 != right.size()) {
						//  A -> ... B beta
						auto beta = std::vector(right.begin() + i + 1, right.end());
						auto fiBeta = first_of(beta);  //  FI(beta)
						if (fiBeta.count(gra::epsilon)) {
							follow[B].insert(follow[A].begin(), follow[A].end());
						}
						fiBeta.erase(gra::epsilon);
						follow[B].merge(std::move(fiBeta));
					} else {
						//  A -> ... B
						follow[B].insert(follow[A].begin(), follow[A].end());
					}
					auto afterSZ = follow[B].size();
					changed |= (beforeSZ != afterSZ);
				}
			}
		}
		
	} while (changed);
}

void LL1Analyzer::analyze_epsilon_reachable() {
	auto vis = std::map<std::string, bool>();
	auto st = std::stack<std::string>();
	st.push(gra::epsilon);
	while (!st.empty()) {
		auto u = st.top();
		st.pop();
		if (vis[u]) { continue; }
		vis[u] = true;
		toEpsilon.insert(u);
		for (auto & rule: allRules) {
			auto & left = rule.first;
			for (auto & right: rule.second) {
				if (right.size() == 1 && right[0] == gra::epsilon) {
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
	{
		lLog.info("Follow:");
		moe_r_set(lLog.indent, lLog.indent + 1);
		for (auto & x: vocabulary) {
			lLog.info(x);
			moe_r_set(lLog.indent, lLog.indent + 1);
			auto buf = std::string();
			for (auto & y: follow[x]) {
				buf += y;
				buf += ' ';
			}
			lLog.info(buf);
		}
	}
}

std::set<std::string> LL1Analyzer::first_of(const std::vector<std::string> & items) {
//	moe_dbg(items);
	auto res = std::set<std::string>();
	auto brk = false;
	for (auto & item: items) {
		if (item == gra::epsilon) {
		
		} else {
			auto tmp = first[item];
			tmp.erase(gra::epsilon);
			res.insert(tmp.begin(), tmp.end());
			if (!first[item].count(gra::epsilon)) {
				brk = true;
				break;
			}
		}
	}
	if (!brk) {
		res.insert(gra::epsilon);
	}
//	moe_dbg(res);
	return res;
}

void LL1Analyzer::get_table() {
	for (const auto & [A, leftRules]: allRules) {
		for (const auto & yeta: leftRules) {
			auto firstOfYeta = first_of(yeta);
			auto followA = follow[A];
			for (const auto & a: vocabulary) {
				if (!isTerm[a]) {
					continue;
				}
				if (firstOfYeta.count(a)) {
					table[A][a] = std::make_pair(A, yeta);
				}
				if (firstOfYeta.count(gra::epsilon) && followA.count(a)) {
					table[A][a] = std::make_pair(A, yeta);
				}
			}
			if (firstOfYeta.count(gra::epsilon) && followA.count(gra::endLabel)) {
				table[A][gra::endLabel] = std::make_pair(A, yeta);
			}
		}
	}
}


void
LL1Analyzer::to_ll1_parser_info(std::string_view filePath, std::string_view parserName) {
	auto ofs = std::ofstream(filePath);
	//  head
	ofs << "#pragma once" << std::endl;
	ofs << "#include <map>" << std::endl;
	ofs << "#include <vector>" << std::endl;
	ofs << "#include <iostream>" << std::endl;
	ofs << "#include <set>" << std::endl;
	ofs << "#include <utility>" << std::endl;
	ofs << std::endl << std::endl << std::endl;
	ofs << "namespace " << parserName << "{" << std::endl;
	
	//  Parser rule type
	ofs << "enum class RuleType {" << std::endl;
	for (auto & v: vocabulary) {
		ofs << "\t" << v << "," << std::endl;
	}
	ofs << "\t" << gra::epsilon << "," << std::endl;
	ofs << "\t" << gra::endLabel << "," << std::endl;
	ofs << "};" << std::endl << std::endl;
	// Parser rule type finished.
	
	//  strToRuleType function
	ofs << "static RuleType strToRuleType(std::string_view str) {" << std::endl;
	ofs << "\tif (str.empty()) {" << std::endl;
	ofs << "\t\tstd::cerr << \"Input string is empty!\" << std::endl;" << std::endl;
	ofs << "\t\texit(-1);" << std::endl;
	ofs << "\t}";
	for (auto & v: vocabulary) {
		ofs << " else if (str == \"" << v << "\") {" << std::endl;
		ofs << "\t\treturn RuleType::" << v << ";" << std::endl;
		ofs << "\t}";
	}
	ofs << " else if (str == \"" << gra::epsilon << "\") {" << std::endl;
	ofs << "\t\treturn RuleType::" << gra::epsilon << ";" << std::endl;
	ofs << "\t}";
	ofs << " else if (str == \"" << gra::endLabel << "\") {" << std::endl;
	ofs << "\t\treturn RuleType::" << gra::endLabel << ";" << std::endl;
	ofs << "\t}";
	ofs << " else {" << std::endl;
	ofs << "\t\tstd::cerr << \"Unknown rule type.\" << std::endl;" << std::endl;
	ofs << "\t\texit(-1);" << std::endl;
	ofs << "\t}";
	ofs << std::endl;
	ofs << "}" << std::endl << std::endl;
	//  strToRuleType function end.
	
	//  ruleTypeToStr function
	ofs << "static std::string ruleTypeToStr(RuleType ruleType) {" << std::endl;
	ofs << "\tif (0) {" << std::endl;
	ofs << "\t}";
	for (auto & v: vocabulary) {
		ofs << " else if (ruleType == RuleType::" << v << ") {" << std::endl;
		ofs << "\t\treturn \"" << v << "\";" << std::endl;
		ofs << "\t}";
	}
	ofs << " else if (ruleType == RuleType::" << gra::epsilon << ") {" << std::endl;
	ofs << "\t\treturn \"" << gra::epsilon << "\";" << std::endl;
	ofs << "\t}";
	ofs << " else if (ruleType == RuleType::" << gra::endLabel << ") {" << std::endl;
	ofs << "\t\treturn \"" << gra::endLabel << "\";" << std::endl;
	ofs << "\t}";
	ofs << " else {" << std::endl;
	ofs << "\t\tstd::cerr << \"Unknown rule type.\" << std::endl;" << std::endl;
	ofs << "\t\texit(-1);" << std::endl;
	ofs << "\t}";
	ofs << std::endl;
	ofs << "}" << std::endl;
	//  strToRuleType function end.
	
	//  allRules
	ofs << "static const std::map<RuleType, std::vector<std::vector<RuleType>>> allRules{"
	    << std::endl;
	for (auto & rule: allRules) {
		auto & left = rule.first;
		ofs << "\t" << "{RuleType::" << left << ", {";
		for (auto & right: rule.second) {
			ofs << "{";
			for (auto & v: right) {
				ofs << "RuleType::" << v << ", ";
			}
			ofs << "}, ";
		}
		ofs << "}}," << std::endl;
	}
	ofs << "};" << std::endl << std::endl;
	//  allRules end.
	
	//  first
	ofs << "static const std::map<RuleType, std::set<RuleType>> first{" << std::endl;
	for (auto & pa: first) {
		auto & left = pa.first;
		ofs << "\t{RuleType::" << left << ", {";
		for (auto & item: pa.second) {
			ofs << "RuleType::" << item << ", ";
		}
		ofs << "}}," << std::endl;
	}
	ofs << "};" << std::endl << std::endl;
	//  first end.
	
	//  follow
	ofs << "static const std::map<RuleType, std::set<RuleType>> follow{" << std::endl;
	for (auto & pa: follow) {
		auto & left = pa.first;
		ofs << "\t{RuleType::" << left << ", {";
		for (auto & item: pa.second) {
			ofs << "RuleType::" << item << ", ";
		}
		ofs << "}}," << std::endl;
	}
	ofs << "};" << std::endl << std::endl;
	//  follow end.
	
	//  table
	ofs << "static const std::map<\n"
	    << "\tRuleType, std::map<RuleType, std::pair<RuleType, std::vector<RuleType>>>\n"
	    << "> table{"
	    << std::endl;
	for (const auto & [left, row]: table) {
		//  one element of std::map<..., ...>
		ofs << "\t{";
		ofs << "RuleType::" << left << ", ";
		//  std::map<..., ...>
		ofs << "{";
		for (const auto & [right, rule]: row) {
			//  one element of std::map<..., ...>
			ofs << "{";
			ofs << "RuleType::" << right << ", ";
			//  std::pair<..., ...>
			ofs << "{";
			//  first element of std::pair
			ofs << "RuleType::" << rule.first << ", {";
			//  second element of std::pair, std::vector<...>
			for (const auto & a: rule.second) {
				ofs << "RuleType::" << a << ", ";
			}
			ofs << "}}, ";
			ofs << "}, ";
		}
		ofs << "}}," << std::endl;
	}
	ofs << "};" << std::endl << std::endl;
	//  table end.
	
	//  term
	ofs << "static const std::set<RuleType> terms{" << std::endl;
	for (auto & pa: isTerm) {
		if (pa.second) {
			ofs << "\tRuleType::" << pa.first << "," << std::endl;
		}
	}
	ofs << "};" << std::endl << std::endl;
	//  term end.
	
	//  start rule
	ofs << "static const RuleType start = RuleType::" << gra::startStateName << ";"
	    << std::endl << std::endl;
	//  end rule
	ofs << "static const RuleType end = RuleType::" << gra::endLabel << ";" << std::endl
	    << std::endl;
	//  epsilon rule
	ofs << "static const RuleType epsilon = RuleType::" << gra::epsilon << ";"
	    << std::endl << std::endl;
	
	
	ofs << "}" << std::endl;
}

void LL1Analyzer::analyze() {
	analyze_epsilon_reachable();
	get_first();
	get_follow();
	get_table();
}

}
