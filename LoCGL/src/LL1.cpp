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
}

void LL1Analyzer::get_follow() {
	moe_todo();
}

}
