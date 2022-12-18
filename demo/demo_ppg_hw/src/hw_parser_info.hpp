#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <set>
#include <utility>



namespace hw_parser_info{
enum class RuleType {
	BeginStmt,
	ChD,
	ChS,
	ChSep,
	CompUnit,
	EndStmt,
	X,
	Y,
	_epsilon,
	_end,
};

static RuleType strToRuleType(std::string_view str) {
	if (str.empty()) {
		std::cerr << "Input string is empty!" << std::endl;
		exit(-1);
	} else if (str == "BeginStmt") {
		return RuleType::BeginStmt;
	} else if (str == "ChD") {
		return RuleType::ChD;
	} else if (str == "ChS") {
		return RuleType::ChS;
	} else if (str == "ChSep") {
		return RuleType::ChSep;
	} else if (str == "CompUnit") {
		return RuleType::CompUnit;
	} else if (str == "EndStmt") {
		return RuleType::EndStmt;
	} else if (str == "X") {
		return RuleType::X;
	} else if (str == "Y") {
		return RuleType::Y;
	} else if (str == "_epsilon") {
		return RuleType::_epsilon;
	} else if (str == "_end") {
		return RuleType::_end;
	} else {
		std::cerr << "Unknown rule type." << std::endl;
		exit(-1);
	}
}

static std::string ruleTypeToStr(RuleType ruleType) {
	if (0) {
	} else if (ruleType == RuleType::BeginStmt) {
		return "BeginStmt";
	} else if (ruleType == RuleType::ChD) {
		return "ChD";
	} else if (ruleType == RuleType::ChS) {
		return "ChS";
	} else if (ruleType == RuleType::ChSep) {
		return "ChSep";
	} else if (ruleType == RuleType::CompUnit) {
		return "CompUnit";
	} else if (ruleType == RuleType::EndStmt) {
		return "EndStmt";
	} else if (ruleType == RuleType::X) {
		return "X";
	} else if (ruleType == RuleType::Y) {
		return "Y";
	} else if (ruleType == RuleType::_epsilon) {
		return "_epsilon";
	} else if (ruleType == RuleType::_end) {
		return "_end";
	} else {
		std::cerr << "Unknown rule type." << std::endl;
		exit(-1);
	}
}
static const std::map<RuleType, std::vector<std::vector<RuleType>>> allRules{
	{RuleType::CompUnit, {{RuleType::BeginStmt, RuleType::ChD, RuleType::ChSep, RuleType::X, RuleType::EndStmt, }, }},
	{RuleType::X, {{RuleType::ChD, RuleType::ChSep, RuleType::X, }, {RuleType::ChS, RuleType::Y, }, }},
	{RuleType::Y, {{RuleType::ChSep, RuleType::ChS, RuleType::Y, }, {RuleType::_epsilon, }, }},
};

static const std::map<RuleType, std::set<RuleType>> first{
	{RuleType::BeginStmt, {RuleType::BeginStmt, }},
	{RuleType::ChD, {RuleType::ChD, }},
	{RuleType::ChS, {RuleType::ChS, }},
	{RuleType::ChSep, {RuleType::ChSep, }},
	{RuleType::CompUnit, {RuleType::BeginStmt, }},
	{RuleType::EndStmt, {RuleType::EndStmt, }},
	{RuleType::X, {RuleType::ChD, RuleType::ChS, }},
	{RuleType::Y, {RuleType::ChSep, RuleType::_epsilon, }},
	{RuleType::_epsilon, {}},
};

static const std::map<RuleType, std::set<RuleType>> follow{
	{RuleType::BeginStmt, {RuleType::ChD, }},
	{RuleType::ChD, {RuleType::ChSep, }},
	{RuleType::ChS, {RuleType::ChSep, RuleType::EndStmt, }},
	{RuleType::ChSep, {RuleType::ChD, RuleType::ChS, }},
	{RuleType::CompUnit, {RuleType::_end, }},
	{RuleType::EndStmt, {RuleType::_end, }},
	{RuleType::X, {RuleType::EndStmt, }},
	{RuleType::Y, {RuleType::EndStmt, }},
	{RuleType::_epsilon, {RuleType::EndStmt, }},
};

static const std::map<
	RuleType, std::map<RuleType, std::pair<RuleType, std::vector<RuleType>>>
> table{
	{RuleType::CompUnit, {{RuleType::BeginStmt, {RuleType::CompUnit, {RuleType::BeginStmt, RuleType::ChD, RuleType::ChSep, RuleType::X, RuleType::EndStmt, }}, }, }},
	{RuleType::X, {{RuleType::ChD, {RuleType::X, {RuleType::ChD, RuleType::ChSep, RuleType::X, }}, }, {RuleType::ChS, {RuleType::X, {RuleType::ChS, RuleType::Y, }}, }, }},
	{RuleType::Y, {{RuleType::ChSep, {RuleType::Y, {RuleType::ChSep, RuleType::ChS, RuleType::Y, }}, }, {RuleType::EndStmt, {RuleType::Y, {RuleType::_epsilon, }}, }, }},
};

static const std::set<RuleType> terms{
	RuleType::BeginStmt,
	RuleType::ChD,
	RuleType::ChS,
	RuleType::ChSep,
	RuleType::EndStmt,
};

static const RuleType start = RuleType::CompUnit;

static const RuleType end = RuleType::_end;

static const RuleType epsilon = RuleType::_epsilon;

}
