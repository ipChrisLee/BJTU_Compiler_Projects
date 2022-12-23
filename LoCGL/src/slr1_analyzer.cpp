#include "slr1_analyzer.hpp"

#include <queue>

#include <moe/rt_check.hpp>
#include <moe/stl_pro.hpp>
#include <moe/log.hpp>

namespace slr1 {

//  COPY FROM ll1_analyzer.cpp
//  change some api used to allRules
void SLR1Analyzer::get_first() {
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
			for (const auto & [_, rule]: allRules[x]) {
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
					for (auto & y: rule) {
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

void SLR1Analyzer::get_follow() {
	moe_assert(vocabulary.count(gra::startStateName), "`CompUnit` not found!");
	follow[gra::startStateName].insert(gra::endLabel);
	auto changed = false;
	do {
		changed = false;
		for (auto & rule: allRules) {
			auto & A = rule.first;
//			moe_slog_info(A);
			for (auto & [_, right]: rule.second) {
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

std::set<std::string> SLR1Analyzer::first_of(const std::vector<std::string> & items) {
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

void SLR1Analyzer::analyze_epsilon_reachable() {
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
			for (auto & [_, right]: rule.second) {
				if (right.size() == 1 && right[0] == gra::epsilon) {
					if (!vis[left]) {
						st.push(left);
					}
				}
			}
		}
	}
}

void SLR1Analyzer::analyze() {
	analyze_epsilon_reachable();
	get_first();
	get_follow();
	get_graph();
}

void SLR1Analyzer::log_it(moe::LocalLog & lLog) {
	gra::GraP::log_it(lLog);
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
	{
		lLog.info("Graph nodes:");
		moe_r_set(lLog.indent, lLog.indent + 1);
		for (const auto & [id, content]: id2content) {
			lLog.info(std::to_string(id) + ": ");
			moe_r_set(lLog.indent, lLog.indent + 1);
			content.log_it(lLog);
		}
	}
	{
		lLog.info("Graph edges:");
		moe_r_set(lLog.indent, lLog.indent + 1);
		for (auto & [u, vs]: edges) {
			for (auto & v: vs) {
				lLog.info(
					std::to_string(u) + " -> " + std::to_string(v.second) + " % " +
						v.first
				);
			}
		}
	}
}
//  COPY END


void SLR1Analyzer::get_graph() {
	auto lLog = moe_llog("logs/liaspg/process_of_gettable.txt", " ", false, "//");
	auto q = std::queue<NodeID_t>();
	{   //  the first one
		moe_assert(
			allRules[gra::startStateName].size() == 1,
			"CompUnit can only have one rule."
		);
		auto startItems = allRules[gra::startStateName].begin()->second;
		startItems.emplace(startItems.begin(), gra::dot);
		auto nodeStartContent = NodeContent{
			.stmts={{gra::startStateName, startItems}},
		};
		nodeStartContent = nodeStartContent.closure_operation(*this);
		start = cnt++;
		content2id[nodeStartContent] = start;
		id2content[start] = nodeStartContent;
		q.push(start);
		lLog.info("The first node content:");
		moe_r_set(lLog.indent, lLog.indent + 1);
		nodeStartContent.log_it(lLog);
	}
	while (!q.empty()) {
		auto now = q.front();
		q.pop();
		lLog.info("For node[", now, "]");
		moe_r_set(lLog.indent, lLog.indent + 1);
		auto nowContent = id2content[now];
		for (const auto & a: vocabulary) {
			auto nxtContent = nowContent.read_operation(a).closure_operation(*this);
			if (nxtContent.stmts.empty()) {
				continue;
			}
			{
				lLog.info("Got:");
				moe_r_set(lLog.indent, lLog.indent + 1);
				nxtContent.log_it(lLog);
			}
			auto nxt = NodeID_t(0);
			if (!content2id.count(nxtContent)) {
				nxt = cnt++;
				content2id[nxtContent] = nxt;
				id2content[nxt] = nxtContent;
				q.push(nxt);
				lLog.info("To [", nxt, "]");
			} else {
				nxt = content2id[nxtContent];
			}
			edges[now][a] = nxt;
		}
	}
	{
		//  find end
		auto endRuleLeft = gra::startStateName;
		auto endRuleRight = allRules[gra::startStateName].begin()->second;
		endRuleRight.emplace_back(gra::dot);
		for (auto & [content, id]: content2id) {
			if (content.stmts.count(std::make_pair(endRuleLeft, endRuleRight))) {
				end = id;
			}
		}
	}
	moe_assert(end != NodeID_t(-1));
}

void SLR1Analyzer::to_slr1_parser_info(
	std::string_view filePath, std::string_view parserName
) {
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
	//  head end.
	
	//  Parser rule type
	{
		ofs << "enum class RuleType {" << std::endl;
		for (auto & v: vocabulary) {
			ofs << "\t" << v << "," << std::endl;
		}
		ofs << "\t" << gra::epsilon << "," << std::endl;
		ofs << "\t" << gra::endLabel << "," << std::endl;
		ofs << "};" << std::endl << std::endl;
	}
	// Parser rule type finished.
	
	//  strToRuleType function
	{
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
		ofs << "\t\tstd::cerr << \"Unknown rule name [\" << str << \"].\" << std::endl;" << std::endl;
		ofs << "\t\texit(-1);" << std::endl;
		ofs << "\t}";
		ofs << std::endl;
		ofs << "}" << std::endl << std::endl;
	}
	//  strToRuleType function end.
	
	//  ruleTypeToStr function
	{
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
	}
	//  strToRuleType function end.
	
	//  ParseType
	{
		ofs << "enum class ParseType {" << std::endl;
		for (auto & [_, m]: allRules) {
			for (auto & [f, _1]: m) {
				ofs << "\t" << f << "," << std::endl;
			}
		}
		ofs << "};" << std::endl << std::endl;
	}
	//  ParseType end.
	
	//  strToParseType function.
	{
		ofs << "static ParseType strToParseType(std::string_view str) {" << std::endl;
		ofs << "\tif (0) {" << std::endl;
		ofs << "\t}";
		for (auto & [_, m]: allRules) {
			for (auto & [f, _1]: m) {
				ofs << " else if (str == \"" << f << "\") {" << std::endl;
				ofs << "\t\treturn ParseType::" << f << ";" << std::endl;
				ofs << "\t}";
			}
		}
		ofs << " else {" << std::endl;
		ofs << "\t\tstd::cerr << \"Unknown parse type name [\" << str << \"].\" << std::endl;"
		    << std::endl;
		ofs << "\t\texit(-1);" << std::endl;
		ofs << "\t}" << std::endl;
		ofs << "}" << std::endl << std::endl;
	}
	//  strToParseType end.
	
	//  parseTypeToStr function.
	{
		ofs << "static std::string parseTypeToStr(ParseType parseType) {" << std::endl;
		ofs << "\tif (0) {" << std::endl;
		ofs << "\t}";
		for (auto & [_, m]: allRules) {
			for (auto & [f, _1]: m) {
				ofs << " else if (parseType == ParseType::" << f << ") {" << std::endl;
				ofs << "\t\treturn \"" << f << "\";" << std::endl;
				ofs << "\t}";
			}
		}
		ofs << " else {" << std::endl;
		ofs << "\t\tstd::cerr << \"Unknown rule type.\" << std::endl;" << std::endl;
		ofs << "\t\texit(-1);" << std::endl;
		ofs << "\t}";
		ofs << std::endl;
		ofs << "}" << std::endl << std::endl;
	}
	//  parseTypeToStr end.
	
	//  actionTables
	{
		ofs << "using NodeID_t = uint64_t;" << std::endl;
		//  actionTableS
		{
			ofs << "static std::map<NodeID_t, std::map<RuleType, NodeID_t>> actionTableS = {"
			    << std::endl;
			for (auto & [u, es]: edges) {
				auto sEs = std::map<std::string, NodeID_t>();
				for (auto & [a, v]: es) {
					if (isTerm[a] || a == gra::endLabel) {
						if (u == end) {
							//  TODO: may need something else?
							sEs.emplace(a, v);
						} else {
							sEs.emplace(a, v);
						}
					}
				}
				if (!sEs.empty()) {
					ofs << "\t{" << u << ", {";
					for (auto & [a, v]: sEs) {
						ofs << "{RuleType::" << a << ", " << v << "}, ";
					}
					ofs << "}}," << std::endl;
				}
			}
			ofs << "};" << std::endl;
		}
		//  actionTableG
		{
			ofs << "static std::map<NodeID_t, std::map<RuleType, NodeID_t>> actionTableG = {"
			    << std::endl;
			for (auto & [u, es]: edges) {
				auto gEs = std::map<std::string, NodeID_t>();
				for (auto & [a, v]: es) {
					if (!isTerm[a] && a != gra::endLabel) {
						gEs.emplace(a, v);
					}
				}
				if (!gEs.empty()) {
					ofs << "\t{" << u << ", {";
					for (auto & [a, v]: gEs) {
						ofs << "{RuleType::" << a << ", " << v << "}, ";
					}
					ofs << "}}," << std::endl;
				}
			}
			ofs << "};" << std::endl;
		}
		//  actionTableR
		{
			auto vocabularyWithEnd = vocabulary;
			vocabularyWithEnd.insert(gra::endLabel);
			auto lLog = moe_llog("logs/liaspg/table_r_process.txt", " ", false, "//");
			ofs << "static std::map<NodeID_t, std::map<RuleType, ParseType>> actionTableR = {"
			    << std::endl;
			for (auto & [id, content]: id2content) {
				auto rRule = std::vector<std::string>();
				auto thisA = std::string();
				lLog.info(id);
				moe_r_set(lLog.indent, lLog.indent + 1);
				for (auto [A, yeta]: content.stmts) {
					lLog.info(
						A,
						"->",
						[](auto & _yeta) {
							auto buf = std::string();
							std::for_each(
								_yeta.begin(), _yeta.end(), [&buf](auto s) {
									buf += s + " ";
								}
							);
							return buf;
						}(yeta)
					);
					if (*yeta.rbegin() == gra::dot && A != gra::startStateName) {
						yeta.pop_back();
						thisA = A;
						rRule.emplace_back(ruleToName[std::make_pair(std::move(A), std::move(yeta))]);
						lLog.info("hit");
					}
				}
				lLog.info("thisA =", thisA);
				if (rRule.empty()) {
					continue;
				}
				moe_assert(rRule.size() == 1);
				moe_assert(!rRule.begin()->empty());
				auto parseRuleName = *rRule.begin();
				ofs << "\t{" << id << ", " << "{";
				for (auto & a: vocabularyWithEnd) {
					lLog.info(a);
					if ((isTerm[a] || a == gra::endLabel) && follow[thisA].count(a)) {
						ofs << "{RuleType::" << a << ", ParseType::" << parseRuleName << "}, ";
					}
				}
				ofs << "}}," << std::endl;
			}
			ofs << "};" << std::endl;
		}
	}
	//  table end.
	
	//  parse rule type to stmt
	{
		// std::map<ParseType, std::pair<RuleType, std::vector<RuleType>>> ruleNameToRule;
		ofs
			<< "static std::map<ParseType, std::pair<RuleType, std::vector<RuleType>>> parseTypeToRule = {"
			<< std::endl;
		for (auto & [A, nameAndYeta]: allRules) {
			for (auto & [parseName, yeta]: nameAndYeta) {
				ofs << "\t{ParseType::" << parseName << ", {RuleType::" << A << ", {";
				for (auto & a: yeta) {
					ofs << "RuleType::" << a << ", ";
				}
				ofs << "}}}," << std::endl;
			}
		}
		ofs << "};" << std::endl << std::endl;
	}
	//  parse rule type to stmt
	
	//  start and end
	ofs << "static NodeID_t start = " << start << ";" << std::endl;
	ofs << "static NodeID_t end = " << end << ";" << std::endl << std::endl;
	//  start and end end.
	
	//  some special rules
	ofs << "static RuleType startRule = RuleType::" << gra::startStateName << ";" << std::endl;
	ofs << "static RuleType endRule = RuleType::" << gra::endLabel << ";" << std::endl << std::endl;
	//  some special rules end.
	
	//  the only rule of start
	{
		auto theFirstParseType = allRules[gra::startStateName].begin()->first;
		ofs << "static ParseType theFirstParseType = ParseType::" << theFirstParseType << ";"
		    << std::endl << std::endl;
	}
	//  the only rule of start end.
	
	//  end of namespace
	ofs << "}" << std::endl;
}


}