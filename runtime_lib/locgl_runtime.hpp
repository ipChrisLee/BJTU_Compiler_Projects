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

#include "general_ast.hpp"


namespace locgl_runtime {

template<typename RuleType>
struct Rule {
	static_assert(std::is_enum<RuleType>::value, "Template argument should be enum.");
	RuleType tokenType;
	std::string content;
	
	Rule(
		std::string_view src,
		std::function<RuleType(std::string_view str)> & strToRuleType
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
		assert(res.size() > 2);
		tokenType = strToRuleType(res[0]);
		for (auto i = size_t(1); i < res.size(); ++i) {
			assert(res[i].size() == 1);
			content.push_back(res[i][0]);
		}
	}
	
	Rule(const Rule &) = default;
	
	Rule(Rule &&) noexcept = default;
};

template<typename RuleType>
struct Parser {
	std::map<RuleType, std::vector<std::vector<RuleType>>> allRules;
	std::map<RuleType, std::vector<RuleType>> first, follow;
	std::set<RuleType> terms;   //  terminators
	RuleType start;    //  CompUnit
	RuleType end;      //  # or _end
	RuleType epsilon;  //   $ or _epsilon
	
	std::set<RuleType> first_of(const std::vector<RuleType> & items) {
		auto res = std::set<RuleType>();
		auto itemSet = std::set<RuleType>(items.begin(), items.end());
		auto brk = false;
		for (auto & item: itemSet) {
			auto tmp = first[item];
			tmp.erase(epsilon);
			res.insert(tmp.begin(), tmp.end());
			if (!first[item].count(epsilon)) {
				brk = true;
				break;
			}
		}
		if (!brk) {
			res.insert(epsilon);
		}
		return res;
	}
	
	std::shared_ptr<gast::ASTNode<RuleType>>
	parse(std::vector<Rule<RuleType>> items) {
		items.emplace_back(end, "");
		auto idx = size_t(0);
		auto now = std::make_shared<gast::ASTNode<RuleType>>(start, "", { }, nullptr);
		while (true) {
			auto nowRule = now->ruleType;
//			auto fnd = false;
			for (auto & rule: allRules[nowRule]) {
				if (first_of(rule).count(items[idx])) {
//					fnd = true;
					auto nxt = std::make_shared<gast::ASTNode<RuleType>>(
						items[0], "", { }, std::weak_ptr(now));
					now->sons.emplace_back(std::move(nxt));
				}
			}
			
		}
		return now;
	}
};
}