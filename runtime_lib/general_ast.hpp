#pragma once

#include <string>
#include <type_traits>
#include <memory>


namespace gast { //  general ast

template<typename RuleType>
struct ASTNode {
	static_assert(std::is_enum<RuleType>::value, "Template argument should be enum.");
	
	RuleType ruleType;
	std::string content;    //  only for terminator
	//  TODO: change content type to `std::optional`.
	std::vector<std::shared_ptr<ASTNode<RuleType>>> sons;
	std::weak_ptr<ASTNode<RuleType>> fa;
	
	ASTNode(
		RuleType ruleType, std::string content,
		std::vector<std::shared_ptr<ASTNode<RuleType>>> sons,
		std::weak_ptr<ASTNode<RuleType>> fa
	) :
		ruleType(ruleType),
		content(std::move(content)),
		sons(std::move(sons)),
		fa(std::move(fa)) {
	}
	
	std::string to_dot(std::function<std::string(RuleType)> ruleTypeToStr) const {
		auto res = std::string();
		res += std::to_string(uint64_t(this)) + " [label = \"" + ruleTypeToStr(ruleType) +
			"(" + content + ")\"]" + "\n";
		for (auto & son: sons) {
			res += std::to_string(uint64_t(this)) + " -> " +
				std::to_string(uint64_t(son.get())) + "\n";
			res += son->to_dot(ruleTypeToStr);
		}
		return res;
	}
	
};

}