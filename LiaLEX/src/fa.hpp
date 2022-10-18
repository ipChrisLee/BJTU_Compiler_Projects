#pragma once

#include <memory>
#include <map>
#include <optional>
#include <set>
#include "regex_analyze.hpp"
#include "lialex_runtime.hpp"
#include "moe/log.hpp"


struct FAEdge;

struct FANode {
	std::map<char, std::vector<FAEdge>> edges;
	std::optional<Rule> rule;                       //  End for rule.
};

struct FAEdge {
	std::weak_ptr<FANode> from;
	char ch;
	std::weak_ptr<FANode> to;
};

struct FA {
	std::set<std::shared_ptr<FANode>> pool;
	std::shared_ptr<FANode> beginNode;
	/*  For sub fa, there is some end status without rule, which is saved here. */
	std::set<std::shared_ptr<FANode>> endNodes;
	
	FA() = default;
	
	//  Create a fa which can accepts a char.
	explicit FA(char ch);
	
	void log_it(moe::LocalLog & lLog) const;
	
	static void add_edge(const FAEdge & edge);
};

//  build on `F*` regex.
FA build_with_multi(FA && fa);

//  build on `fal | far`
FA build_with_or_cond(FA && fal, FA && far);

//  build on `fal ~ far`
FA build_with_cat(FA && fal, FA && far);

FA fa_from_regex_ast(const RegexASTNode & root);

FA merge_all(
	const std::map<Rule, std::unique_ptr<RegexASTNode>> & ruleAndRegexAST
);

FA nfa2dfa(const FA & nfa);

void genHppBasingOnLex(
	const FA & dfa, const std::string & filePath, const std::string & lexName,
	const std::vector<Rule> & rules
);
