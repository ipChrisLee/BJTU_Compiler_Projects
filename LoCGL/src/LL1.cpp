#include "LL1.hpp"


namespace ll1 {

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
			moe_slog_info(A);
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
	auto itemSet = std::set<std::string>(items.begin(), items.end());
	auto brk = false;
	for (auto & item: itemSet) {
		auto tmp = first[item];
		tmp.erase(gra::epsilon);
		res.insert(tmp.begin(), tmp.end());
		if (!first[item].count(gra::epsilon)) {
			brk = true;
			break;
		}
	}
	if (!brk) {
		res.insert(gra::epsilon);
	}
//	moe_dbg(res);
	return res;
}
}
