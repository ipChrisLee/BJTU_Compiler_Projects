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
	
};
}