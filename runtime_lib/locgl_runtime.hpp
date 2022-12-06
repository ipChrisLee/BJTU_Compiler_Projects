#pragma once


#include <cstdint>
#include <string>
#include <memory>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <string_view>
#include <functional>
#include <charconv>
#include <stack>
#include <moe/rt_check.hpp>
#include <moe/debugger.hpp>

#include "general_ast.hpp"


namespace locgl_ll1_runtime {

template<typename RuleType>
struct Rule {
	static_assert(std::is_enum<RuleType>::value, "Template argument should be enum.");
	RuleType ruleType;
	std::string content;
	
	Rule(RuleType ruleType, std::string content) :
		ruleType(ruleType), content(std::move(content)) {
	}
	
	Rule(
		std::string_view src,
		std::function<RuleType(std::string_view)> strToRuleType
	) {
		using namespace std::string_view_literals;
		auto res = std::vector<std::string>();
		auto posStart = std::string_view::size_type(0);
		while (posStart < src.size()) {
			auto iFirstDel = src.size();
			for (auto ch: "\n \t"sv) {
				auto i = src.find(ch, posStart);
				if (i != std::string_view::npos) {
					iFirstDel = std::min(iFirstDel, i);
				}
			}
			if (iFirstDel > posStart) {
				res.emplace_back(src.substr(posStart, iFirstDel - posStart));
			}
			posStart = iFirstDel + 1;
		}
		assert(res.size() >= 2);
		ruleType = strToRuleType(res[0]);
		for (auto i = size_t(1); i < res.size(); ++i) {
//			assert(res[i].size() == 1);
			int32_t tmp;
			std::from_chars(res[i].c_str(), res[i].c_str() + res[i].size(), tmp);
			content.push_back(char(tmp));
		}
	}
	
	Rule(const Rule &) = default;
	
	Rule(Rule &&) noexcept = default;
};


template<typename RuleType>
struct LL1Parser {
	std::map<RuleType, std::vector<std::vector<RuleType>>> allRules;
	std::map<RuleType, std::set<RuleType>> first, follow;
	std::set<RuleType> terms;   //  terminators
	RuleType start;    //  CompUnit
	RuleType end;      //  # or _end
	RuleType epsilon;  //   $ or _epsilon
	std::map<
		RuleType, std::map<RuleType, std::pair<RuleType, std::vector<RuleType>>>
	> table;
	std::function<std::string(RuleType)> ruleTypeToStr;
	
	std::set<RuleType> first_of(const std::vector<RuleType> & items) {
		auto res = std::set<RuleType>();
		auto brk = false;
		for (auto & item: items) {
			if (item == epsilon) {
			
			} else {
				auto tmp = first[item];
				tmp.erase(epsilon);
				res.insert(tmp.begin(), tmp.end());
				if (!first[item].count(epsilon)) {
					brk = true;
					break;
				}
			}
		}
		if (!brk) {
			res.insert(epsilon);
		}
		return res;
	}
	
	void dfs_pp(
		std::shared_ptr<gast::ASTNode<RuleType>> now,
		const std::vector<Rule<RuleType>> items,
		size_t & idx
	) {
//		std::cerr << "Now->ruleType:\t" << int(now->ruleType) << std::endl;
		if (terms.count(now->ruleType) || now->ruleType == epsilon) {
			if (now->ruleType == epsilon) {
			
			} else {
//				std::cerr << int(now->ruleType) << std::endl;
//				std::cerr << int(items[idx].ruleType) << std::endl;
//				std::cerr << items[idx].content << std::endl;
				assert(now->ruleType == items[idx].ruleType);
				now->content = items[idx].content;
				++idx;
			}
		} else {
			auto nowRule = now->ruleType;
			auto fnd = false;
			for (auto & rule: allRules[nowRule]) {
				if (first_of(rule).count(items[idx].ruleType)) {
					fnd = true;
					for (auto sonRule: rule) {
						auto son = std::make_shared<gast::ASTNode<RuleType>>(
							sonRule, "",
							std::vector<std::shared_ptr<gast::ASTNode<RuleType>>>(),
							std::weak_ptr(now));
						now->sons.emplace_back(son);
					}
					break;
				}
			}
			if (!fnd) {
				//  epsilon
				if (follow[now->ruleType].count(items[idx].ruleType) &&
					first[now->ruleType].count(epsilon)) {
					for (auto & rule: allRules[nowRule]) {
						if (first_of(rule).count(epsilon)) {
							for (auto sonRule: rule) {
								auto son = std::make_shared<gast::ASTNode<RuleType>>(
									sonRule, "",
									std::vector<std::shared_ptr<gast::ASTNode<RuleType>>>(),
									std::weak_ptr(now));
								now->sons.emplace_back(son);
							}
							break;
						}
					}
				} else {
					std::cerr << "Not find!" << std::endl;
					exit(-1);
				}
			}
			for (auto & son: now->sons) {
				dfs_pp(son, items, idx);
			}
		}
	}
	
	std::shared_ptr<gast::ASTNode<RuleType>>
	parse_with_pp(std::vector<Rule<RuleType>> items) {
		//  parse with predictive parse(递归下降法)
		items.emplace_back(end, "");
		auto idx = size_t(0);
		auto now = std::make_shared<gast::ASTNode<RuleType>>(
			start, "", std::vector<std::shared_ptr<gast::ASTNode<RuleType>>>(),
			std::weak_ptr<gast::ASTNode<RuleType>>());
		dfs_pp(now, items, idx);
		return now;
	}
	
	static std::vector<Rule<RuleType>>
	gen_from_str(
		std::string_view src, std::function<RuleType(std::string_view)> strToRuleType
	) {
		using namespace std::string_view_literals;
		auto res = std::vector<Rule<RuleType>>();
		auto posStart = std::string_view::size_type(0);
		while (posStart < src.size()) {
			auto iFirstDel = src.size();
			for (auto ch: "\n"sv) {
				auto i = src.find(ch, posStart);
				if (i != std::string_view::npos) {
					iFirstDel = std::min(iFirstDel, i);
				}
			}
			if (iFirstDel > posStart) {
				res.emplace_back(
					src.substr(posStart, iFirstDel - posStart), strToRuleType
				);
			}
			posStart = iFirstDel + 1;
		}
		return res;
	}
	
	std::shared_ptr<gast::ASTNode<RuleType>>
	parse_with_table(std::vector<Rule<RuleType>> items) {
		//  parse with predictive parse(递归下降法)
		//  root of the ast
		auto root = std::make_shared<gast::ASTNode<RuleType>>(
			start, "",
			std::vector<std::shared_ptr<gast::ASTNode<RuleType>>>(),
			std::weak_ptr<gast::ASTNode<RuleType>>()
		);
		//  余留输入栈
		auto resStack = std::stack<Rule<RuleType>>();
		resStack.push(Rule<RuleType>(end, ""));
		std::for_each(
			items.rbegin(), items.rend(), [&resStack](const Rule<RuleType> & r) {
				resStack.push(r);
			}
		);
		//  分析栈初始化
		auto anaStack
			= std::stack<
				std::pair<RuleType, std::shared_ptr<gast::ASTNode<RuleType>>>
			>();
		anaStack.push(std::make_pair(end, nullptr));
		anaStack.push(std::make_pair(start, root));
		//  Let's go.
		while (!anaStack.empty()) {
			auto anaTopRuleType = anaStack.top().first;
			auto now = anaStack.top().second;
			auto resTopRule = resStack.top();
			anaStack.pop();
//			moe_dbg("-------");
//			moe_dbg(ruleTypeToStr(anaTopRuleType));
//			moe_dbg(ruleTypeToStr(resTopRule.ruleType));
			if (anaTopRuleType == end) {
				moe_assert(resTopRule.ruleType == end);
				resStack.pop();
				break;
			} else if (anaTopRuleType == resTopRule.ruleType) {
				moe_assert(terms.count(anaTopRuleType));
				now->content = resTopRule.content;
				resStack.pop();
				continue;
			} else {
				moe_assert(
					!terms.count(anaTopRuleType) && (
						terms.count(resTopRule.ruleType) || resTopRule.ruleType == end
					));
				moe_assert(table[anaTopRuleType].count(resTopRule.ruleType));
				auto yeta = table[anaTopRuleType][resTopRule.ruleType].second;
				std::for_each(
					yeta.rbegin(), yeta.rend(),
					[&anaStack, &now, this](const RuleType & ruleType) {
						auto son = std::make_shared<gast::ASTNode<RuleType>>(
							ruleType, "",
							std::vector<std::shared_ptr<gast::ASTNode<RuleType>>>(),
							std::weak_ptr<gast::ASTNode<RuleType>>(now)
						);
						now->sons.insert(now->sons.begin(), son);
						if (ruleType != epsilon) {
							anaStack.template emplace(ruleType, son);
						}
					}
				);
			}
		}
		return root;
	}
};


}
namespace locgl_slr1_runtime {
template<typename RuleType> using Rule = locgl_ll1_runtime::Rule<RuleType>;
using NodeID_t = uint64_t;

template<typename RuleType, typename ParseType>
struct SLR1Parser {
	static_assert(std::is_enum<RuleType>::value && std::is_enum<ParseType>::value);
	
	std::map<NodeID_t, std::map<RuleType, ParseType>> actionTableR; //  r
	std::map<NodeID_t, std::map<RuleType, NodeID_t>> actionTableS;  //  s
	std::map<NodeID_t, std::map<RuleType, NodeID_t>> actionTableG;  //  goto
	NodeID_t start;
	
	RuleType startRule;
	RuleType endRule;
	
	ParseType theFirstParseType;
	
	std::map<ParseType, std::pair<RuleType, std::vector<RuleType>>> parseTypeToRule;
	
	std::function<std::string(RuleType)> ruleTypeToStr;
	std::function<std::string(ParseType)> parseTypeToStr;
	
	[[nodiscard]] bool is_legal() const {
		for (auto & [u, uEdgesInR]: actionTableR) {
			auto vInR = std::set<RuleType>();
			std::for_each(
				uEdgesInR.begin(), uEdgesInR.end(), [&vInR](const auto & p) {
					vInR.insert(p.first);
				}
			);
			if (actionTableS.count(u)) {
				for (auto & [v, _]: actionTableS.find(u)->second) {
					if (vInR.count(v)) {
						return false;
					}
				}
			}
		}
		return true;
	}
	
	static std::vector<Rule<RuleType>>
	gen_from_str(
		std::string_view src, std::function<RuleType(std::string_view)> strToRuleType
	) {
		using namespace std::string_view_literals;
		auto res = std::vector<Rule<RuleType>>();
		auto posStart = std::string_view::size_type(0);
		while (posStart < src.size()) {
			auto iFirstDel = src.size();
			for (auto ch: "\n"sv) {
				auto i = src.find(ch, posStart);
				if (i != std::string_view::npos) {
					iFirstDel = std::min(iFirstDel, i);
				}
			}
			if (iFirstDel > posStart) {
				res.emplace_back(
					src.substr(posStart, iFirstDel - posStart), strToRuleType
				);
			}
			posStart = iFirstDel + 1;
		}
		return res;
	}
	
	std::shared_ptr<gast::ASTNodeWithInfo<RuleType, ParseType>>
	parse_with_table(std::vector<Rule<RuleType>> items) {
		//  parse with predictive parse(递归下降法)
		//  root of the ast
		using ASTNodeW = gast::ASTNodeWithInfo<RuleType, ParseType>;
#define mk_node(...) std::make_shared<ASTNodeW>(__VA_ARGS__)
#define empty_son_fa std::vector<std::shared_ptr<ASTNodeW>>(), std::weak_ptr<ASTNodeW>()
		auto stateStack = std::stack<NodeID_t>();   //  state stack
		auto astNodeStack = std::stack<std::shared_ptr<ASTNodeW>>();    //  symbol stack
		stateStack.emplace(start);
		auto it = items.begin();
		while (it != items.end()) {
			auto stateTop = stateStack.top();
			auto inputRuleType = it->ruleType;
			if (actionTableS[stateTop].count(inputRuleType)) {
				auto nxtState = actionTableS[stateTop][inputRuleType];
				stateStack.emplace(nxtState);
				astNodeStack.emplace(
					mk_node(inputRuleType, it->content, empty_son_fa)
				);
				++it;
			} else if (actionTableR[stateTop].count(inputRuleType)) {
				auto parseType = actionTableR[stateTop][inputRuleType];
				auto & ruleUsing = parseTypeToRule[parseType];
				auto rootOfSubTree = mk_node(ruleUsing.first, "", empty_son_fa, parseType);
				auto sz = parseTypeToRule[parseType].second.size();
				while (sz--) {
					stateStack.pop();
					auto pSon = astNodeStack.top();
					astNodeStack.pop();
					rootOfSubTree->sons.emplace(rootOfSubTree->sons.begin(), pSon);
					pSon->fa = rootOfSubTree;
					moe_assert(ruleUsing.second[sz] == pSon->ruleType);
				}
				stateTop = stateStack.top();
				if (actionTableG[stateTop].count(ruleUsing.first)) {
					auto nxtState = actionTableG[stateTop][ruleUsing.first];
					stateStack.emplace(nxtState);
					astNodeStack.emplace(rootOfSubTree);
				} else {
					moe_panic("");
				}
			} else {
				moe_panic("");
			}
		}
		auto root = mk_node(startRule, "", empty_son_fa, theFirstParseType);
		while (!astNodeStack.empty()) {
			auto son = astNodeStack.top();
			astNodeStack.pop();
			root->sons.emplace(root->sons.begin(), son);
		}
		return root;
#undef mk_node
	}
};
}