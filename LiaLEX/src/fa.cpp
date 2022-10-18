#include "fa.hpp"
#include "moe/debugger.hpp"
#include <climits>
#include <set>
#include <queue>
#include <vector>


FA::FA(char ch) {
	auto s = std::make_shared<FANode>();
	auto t = std::make_shared<FANode>();
	pool.emplace(s);
	pool.emplace(t);
	beginNode = s;
	endNodes.emplace(t);
	auto e = FAEdge{std::weak_ptr<FANode>(s), ch, std::weak_ptr<FANode>(t)};
	s->edges[ch].emplace_back(e);
}

void FA::add_edge(const FAEdge & edge) {
//	moe_dbg(i64(edge.from.lock().get()));
//	moe_dbg(i64(edge.to.lock().get()));
	edge.from.lock()->edges[edge.ch].emplace_back(edge);
}

void FA::log_it(moe::LocalLog & lLog) const {
	lLog.info("digraph NFA{");
	lLog.info(i64(beginNode.get()), "[label = start]");
	for (auto & p: pool) {
		if (p->rule.has_value()) {
			lLog.info(i64(p.get()), "[label =", p->rule.value().name, "]");
		}
		for (auto & ce: p->edges) {
			for (auto & e: ce.second) {
				lLog.info(
					i64(e.from.lock().get()), "->", i64(e.to.lock().get()),
					"[label =", char_to_dot_string(e.ch), "]"
				);
			}
		}
	}
	lLog.info("}");
}

FA build_with_multi(FA && fa) {
	auto u = std::move(fa.beginNode);
	moe_assert(fa.endNodes.size() == 1);
	auto v = *fa.endNodes.begin();
	fa.endNodes.clear();
	FA::add_edge(
		FAEdge{std::weak_ptr<FANode>(v), 0, std::weak_ptr<FANode>(u)}
	);
	auto s = std::make_shared<FANode>();
	auto t = std::make_shared<FANode>();
	auto newFA = FA();
	newFA.pool.emplace(s);
	newFA.pool.emplace(t);
	newFA.beginNode = s;
	newFA.endNodes.emplace(t);
	newFA.pool.merge(std::move(fa.pool));
	FA::add_edge(FAEdge{std::weak_ptr<FANode>(s), 0, std::weak_ptr<FANode>(u)});
	FA::add_edge(FAEdge{std::weak_ptr<FANode>(s), 0, std::weak_ptr<FANode>(t)});
	FA::add_edge(FAEdge{std::weak_ptr<FANode>(v), 0, std::weak_ptr<FANode>(t)});
	return newFA;
}

FA build_with_or_cond(FA && fal, FA && far) {
	auto s = std::make_shared<FANode>();
	auto t = std::make_shared<FANode>();
	auto newFA = FA();
	newFA.pool.emplace(s);
	newFA.pool.emplace(t);
	newFA.beginNode = s;
	newFA.endNodes.emplace(t);
	
	auto ul = std::move(fal.beginNode);
	moe_assert(fal.endNodes.size() == 1);
	auto vl = *fal.endNodes.begin();
	fal.endNodes.clear();
	newFA.pool.merge(std::move(fal.pool));
	
	auto ur = std::move(far.beginNode);
	moe_assert(far.endNodes.size() == 1);
	auto vr = *far.endNodes.begin();
	far.endNodes.clear();
	newFA.pool.merge(std::move(far.pool));
	
	FA::add_edge(FAEdge{std::weak_ptr<FANode>(s), 0, std::weak_ptr<FANode>(ul)});
	FA::add_edge(FAEdge{std::weak_ptr<FANode>(s), 0, std::weak_ptr<FANode>(ur)});
	FA::add_edge(FAEdge{std::weak_ptr<FANode>(vl), 0, std::weak_ptr<FANode>(t)});
	FA::add_edge(FAEdge{std::weak_ptr<FANode>(vr), 0, std::weak_ptr<FANode>(t)});
	return newFA;
}

FA build_with_cat(FA && fal, FA && far) {
	auto s = std::make_shared<FANode>();
	auto t = std::make_shared<FANode>();
	auto newFA = FA();
	newFA.pool.emplace(s);
	newFA.pool.emplace(t);
	newFA.beginNode = s;
	newFA.endNodes.emplace(t);
	
	auto ul = std::move(fal.beginNode);
	moe_assert(fal.endNodes.size() == 1);
	auto vl = *fal.endNodes.begin();
	fal.endNodes.clear();
	newFA.pool.merge(std::move(fal.pool));
	
	auto ur = std::move(far.beginNode);
	moe_assert(far.endNodes.size() == 1);
	auto vr = *far.endNodes.begin();
	far.endNodes.clear();
	newFA.pool.merge(std::move(far.pool));
	
	FA::add_edge(FAEdge{std::weak_ptr<FANode>(s), 0, std::weak_ptr<FANode>(ul)});
	FA::add_edge(FAEdge{std::weak_ptr<FANode>(vl), 0, std::weak_ptr<FANode>(ur)});
	FA::add_edge(FAEdge{std::weak_ptr<FANode>(vr), 0, std::weak_ptr<FANode>(t)});
	
	return newFA;
}

FA fa_from_regex_ast(const RegexASTNode & root) {
	switch (root.infoType) {
		case RegexASTNodeInfoType::ch: {
			auto ch = std::get<char>(root.info);
//			moe_dbg(ch);
			return FA(ch);
		}
		case RegexASTNodeInfoType::op: {
			auto op = std::get<RegexOperator>(root.info);
			switch (op) {
				case RegexOperator::multi: {
					moe_assert(root.children.size() == 1);
					auto fa = fa_from_regex_ast(*root.children[0]);
					return build_with_multi(std::move(fa));
				}
				case RegexOperator::or_cond: {
					moe_assert(root.children.size() == 2);
					auto fal = fa_from_regex_ast(*root.children[0]);
					auto far = fa_from_regex_ast(*root.children[1]);
					return build_with_or_cond(std::move(fal), std::move(far));
				}
				case RegexOperator::concat: {
					moe_assert(root.children.size() == 2);
					auto fal = fa_from_regex_ast(*root.children[0]);
					auto far = fa_from_regex_ast(*root.children[1]);
					return build_with_cat(std::move(fal), std::move(far));
				}
			}
			break;
		}
		case RegexASTNodeInfoType::another_rule:
			moe_panic("There should not be an `another_rule` here!");
	}
}

FA merge_all(const std::map<Rule, std::unique_ptr<RegexASTNode>> & ruleAndRegexAST) {
	auto nfa = []() {
		auto f = FA();
		auto s = std::make_shared<FANode>();
		f.beginNode = s;
		f.pool.emplace(s);
		return f;
	}();
	for (auto & pairRuleAST: ruleAndRegexAST) {
		if (pairRuleAST.first.ruleType == RuleType::Anonymous) {
			continue;
		}
		auto fa = fa_from_regex_ast(*pairRuleAST.second);
		auto lLog =
			moe_llog("logs/nfa/" + pairRuleAST.first.name + ".dot", " ", true, "//");
		fa.log_it(lLog);
		for (auto & p: fa.endNodes) {
			p->rule = pairRuleAST.first;
		}
		FA::add_edge(
			FAEdge{
				nfa.beginNode, 0, fa.beginNode
			}
		);
		nfa.pool.merge(std::move(fa.pool));
	}
	auto lLog = moe_llog("logs/nfa/nfa.dot", " ", true, "//");
	nfa.log_it(lLog);
	return nfa;
}


static std::set<std::shared_ptr<FANode>>
get_epsilon_closure(const std::set<std::shared_ptr<FANode>> & t) {
	moe_slog_disable_here();
	moe_slog_info("====================");
	auto q = std::queue<std::shared_ptr<FANode>>();
	auto vis = std::map<std::shared_ptr<FANode>, bool>();
	for (auto & p: t) {
		q.push(p);
		vis[p] = true;
		moe_slog_info(i64(p.get()));
	}
	moe_slog_info("--------------------");
	auto c = std::set<std::shared_ptr<FANode>>();
	while (!q.empty()) {
		auto u = q.front();
		q.pop();
		c.emplace(u);
		if (u->edges.count('\0')) {
			for (auto & e: u->edges['\0']) {
				if (!vis[e.to.lock()]) {
					q.emplace(e.to);
					vis[e.to.lock()] = true;
				}
			}
		}
	}
	for (auto & p: c) {
		moe_slog_info(i64(p.get()));
	}
	moe_slog_info("^^^^^^^^^^^^^^^^^");
	return c;
}

static std::set<std::shared_ptr<FANode>>
get_T_from_f(std::set<std::shared_ptr<FANode>> & s, char ch) {
	moe_slog_disable_here();
	auto res = std::set<std::shared_ptr<FANode>>();
	for (auto & p: s) {
		if (p->edges.count(ch)) {
			for (auto & e: p->edges[ch]) {
				res.insert(e.to.lock());
			}
		}
	}
	if (ch == '0' || ch == '1') {
		moe_slog_info("====================");
		moe_slog_info(i32(ch));
		for (auto & p: s) {
			moe_slog_info(i64(p.get()));
		}
		moe_slog_info("--------------------");
		for (auto & p: res) {
			moe_slog_info(i64(p.get()));
		}
		moe_slog_info("^^^^^^^^^^^^^^^^^^^^");
	}
	return res;
}

FA nfa2dfa(const FA & nfa) {
	auto dfa = FA();
	auto closure2node
		= std::map<std::set<std::shared_ptr<FANode>>, std::shared_ptr<FANode>>();
	auto node2closure
		= std::map<std::shared_ptr<FANode>, std::set<std::shared_ptr<FANode>>>();
	dfa.beginNode = std::make_shared<FANode>();
	dfa.pool.emplace(dfa.beginNode);
	closure2node[get_epsilon_closure({nfa.beginNode})] = dfa.beginNode;
	node2closure[dfa.beginNode] = get_epsilon_closure({nfa.beginNode});
	auto K = std::set<std::shared_ptr<FANode>>();
//	auto vis = std::map<std::shared_ptr<FANode>, bool>();
	K.emplace(dfa.beginNode);
	while (!K.empty()) {
		auto qi = [&K]() {
			auto _ = K.begin();
			auto r = *_;
			K.erase(_);
			return r;
		}();
//		vis[qi] = true;
		for (auto ch = char(1); ch < CHAR_MAX; ++ch) {
			auto c_qj = get_epsilon_closure(get_T_from_f(node2closure[qi], ch));
//			moe_dbg(c_qj.size());
			if (c_qj.empty()) {
				continue;
			}
			if (!closure2node.count(c_qj)) {
				auto qj = std::make_shared<FANode>();
				dfa.pool.emplace(qj);
				closure2node.emplace(c_qj, qj);
				node2closure.emplace(qj, c_qj);
				K.emplace(qj);
//				moe_dbg(i64(qi.get()));
//				moe_dbg(ch);
//				moe_dbg(i64(qj.get()));
				FA::add_edge(
					FAEdge{
						qi, ch, qj
					}
				);
			} else {
				auto qj = closure2node[c_qj];
//				moe_dbg(i64(qi.get()));
//				moe_dbg(ch);
//				moe_dbg(i64(qj.get()));
				FA::add_edge(
					FAEdge{
						qi, ch, qj
					}
				);
			}
		}
	}
	for (auto & p: dfa.pool) {
//		moe_slog_info("+++++++++++++++++++++++++");
//		moe_slog_info(i64(p.get()));
//		moe_slog_info("=");
		auto ruleVec = std::vector<Rule>();
		for (auto & v: node2closure[p]) {
//			moe_slog_info(i64(v.get()));
			if (v->rule.has_value()) {
				ruleVec.emplace_back(v->rule.value());
			}
		}
		if (!ruleVec.empty()) {
			std::sort(
				ruleVec.begin(), ruleVec.end(),
				[](const auto & rl, const auto & rr) {
					return rl.rank < rr.rank;
				}
			);
			p->rule = ruleVec[0];
		}
//		moe_slog_info("^^^^^^^^^^^^^^^^^^^^^^^^^");
	}
	auto lLog = moe_llog("logs/dfa.dot", " ", true, "//");
	dfa.log_it(lLog);
	return dfa;
}

void genHppBasingOnLex(
	const FA & dfa, const std::string & filePath, const std::string & lexName,
	const std::vector<Rule> & rules
) {
	auto ofs = std::ofstream(filePath);
	ofs << "#pragma once" << std::endl;
	ofs << "#include <map>" << std::endl;
	ofs << "#include <cstdint>" << std::endl;
	ofs << "#include <string>" << std::endl << std::endl << std::endl;
	ofs << "namespace " << lexName << " {" << std::endl;
	ofs << "using NodeID_t = uint64_t;" << std::endl;
	
	//  Token Type
	ofs << "enum class TokenType {" << std::endl;
	for (auto & rule: rules) {
		if (rule.ruleType == RuleType::Normal) {
			ofs << "\t" << rule.name << ", " << std::endl;
		}
	}
	ofs << "};" << std::endl << std::endl;
	//  Token Type Finished.
	
	//  Token to string
	ofs << "inline std::string get_token_type_name(TokenType token) {" << std::endl;
	ofs << "\tswitch (token) {" << std::endl;
	for (auto & rule: rules) {
		if (rule.ruleType == RuleType::Normal) {
			ofs << "\t\tcase TokenType::" << rule.name << ":" << std::endl;
			ofs << "\t\t\treturn \"" << rule.name << "\";" << std::endl;
		}
	}
	ofs << "\t}" << std::endl;
	ofs << "}" << std::endl << std::endl;
	//  Token to string Finished.
	
	//  nodeType
	ofs << "static const std::map<NodeID_t, TokenType> nodeType{" << std::endl;
	for (auto & p: dfa.pool) {
		if (p->rule.has_value()) {
			ofs << "\t{" << i64(p.get()) <<
			    ", TokenType::" << (p->rule->name) << "}," << std::endl;
		}
	}
	ofs << "};" << std::endl << std::endl;
	//  nodeType finished
	
	//  edges
	ofs << "static const "
	    << "std::map<NodeID_t, std::map<char, NodeID_t>> "
	    << "edges{" << std::endl;
	for (auto & p: dfa.pool) {
		ofs << "\t{" << i64(p.get()) << ", {";
		for (auto & e: p->edges) {
			moe_assert(e.second.size() == 1);
			auto v = e.second[0];
			moe_assert(v.ch);
			ofs << "{" << i32(e.first) << ", " << v.to.lock().get() << "},";
		}
		ofs << "}}," << std::endl;
	}
	ofs << "};" << std::endl << std::endl;
	//  edges Finished
	
	ofs << "static const NodeID_t start = " << i64(dfa.beginNode.get()) << ";"
	    << std::endl;
	
	ofs << "}" << std::endl;
	// #include "../LiaLEX/lialex_runtime/lialex_runtime.hpp"
}

