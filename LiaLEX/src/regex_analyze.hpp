#pragma once

#include <string>
#include "moe/moe_typedef.hpp"
#include "moe/moe_macro.hpp"
#include <variant>
#include <memory>
#include <vector>
#include <map>
#include "moe/moe_concept.hpp"


namespace LiaLEX {

enum class RuleType {
	Anonymous,
	Normal,
	Throw,
};

struct Rule {
	std::string name;
	RuleType ruleType;
	i32 rank;
	
	bool operator<(const Rule & rule) const {
		return name < rule.name;
	}
};

enum class RegexOperator {
	multi,
	or_cond,
	concat,
};

std::string regex_operator_to_string(RegexOperator op);

enum class RegexASTNodeInfoType : i32 {
	ch = 0,
	op,
	another_rule,
};


struct RegexASTNode : public moe::Cloneable {
	RegexASTNodeInfoType infoType;
	using Info_t = std::variant<char, RegexOperator, std::string>;
	Info_t info;
	std::vector<std::unique_ptr<RegexASTNode>> children;
	
	RegexASTNode(const RegexASTNode &);
	
	explicit RegexASTNode(char ch);
	
	explicit RegexASTNode(RegexOperator op);
	
	explicit RegexASTNode(std::string anotherRuleName);
	
	RegexASTNode(RegexASTNodeInfoType infoType, Info_t info);
	
	[[nodiscard]] std::string info_to_string() const;
	
	[[nodiscard]] std::unique_ptr<Cloneable>
	clone_to_unique_ptr_to_impl() const override;
};

//  Merge a new node like op .
//                       /  \
//                    left right
std::unique_ptr<RegexASTNode> merge_node(
	std::unique_ptr<RegexASTNode> && pLeft, RegexOperator op,
	std::unique_ptr<RegexASTNode> && pRight
);

//  Merge a new node like op .
//                        |
//                     operand
std::unique_ptr<RegexASTNode> merge_node(
	RegexOperator op,
	std::unique_ptr<RegexASTNode> && pOperand
);

std::map<Rule, std::unique_ptr<RegexASTNode>>
scan_tex_rules(std::string_view filePath);

std::string char_to_dot_string(char c);

}