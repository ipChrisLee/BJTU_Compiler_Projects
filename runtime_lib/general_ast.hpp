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
	std::shared_ptr<ASTNode<RuleType>> sons;
	std::weak_ptr<ASTNode<RuleType>> fa;
};

}