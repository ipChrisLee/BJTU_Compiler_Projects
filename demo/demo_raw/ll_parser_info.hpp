#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <set>
#include <utility>



namespace ll_parser_info{
enum class RuleType {
	A,
	CompUnit,
	E,
	E_,
	Eq,
	F,
	I,
	LParen,
	M,
	RParen,
	T,
	T_,
	V,
	_epsilon,
	_end,
};

static RuleType strToRuleType(std::string_view str) {
	if (str.empty()) {
		std::cerr << "Input string is empty!" << std::endl;
		exit(-1);
	} else if (str == "A") {
		return RuleType::A;
	} else if (str == "CompUnit") {
		return RuleType::CompUnit;
	} else if (str == "E") {
		return RuleType::E;
	} else if (str == "E_") {
		return RuleType::E_;
	} else if (str == "Eq") {
		return RuleType::Eq;
	} else if (str == "F") {
		return RuleType::F;
	} else if (str == "I") {
		return RuleType::I;
	} else if (str == "LParen") {
		return RuleType::LParen;
	} else if (str == "M") {
		return RuleType::M;
	} else if (str == "RParen") {
		return RuleType::RParen;
	} else if (str == "T") {
		return RuleType::T;
	} else if (str == "T_") {
		return RuleType::T_;
	} else if (str == "V") {
		return RuleType::V;
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
	} else if (ruleType == RuleType::A) {
		return "A";
	} else if (ruleType == RuleType::CompUnit) {
		return "CompUnit";
	} else if (ruleType == RuleType::E) {
		return "E";
	} else if (ruleType == RuleType::E_) {
		return "E_";
	} else if (ruleType == RuleType::Eq) {
		return "Eq";
	} else if (ruleType == RuleType::F) {
		return "F";
	} else if (ruleType == RuleType::I) {
		return "I";
	} else if (ruleType == RuleType::LParen) {
		return "LParen";
	} else if (ruleType == RuleType::M) {
		return "M";
	} else if (ruleType == RuleType::RParen) {
		return "RParen";
	} else if (ruleType == RuleType::T) {
		return "T";
	} else if (ruleType == RuleType::T_) {
		return "T_";
	} else if (ruleType == RuleType::V) {
		return "V";
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
	{RuleType::CompUnit, {{RuleType::V, RuleType::Eq, RuleType::E, }, }},
	{RuleType::E, {{RuleType::T, RuleType::E_, }, }},
	{RuleType::E_, {{RuleType::A, RuleType::T, RuleType::E_, }, {RuleType::_epsilon, }, }},
	{RuleType::F, {{RuleType::LParen, RuleType::E, RuleType::RParen, }, {RuleType::I, }, }},
	{RuleType::T, {{RuleType::F, RuleType::T_, }, }},
	{RuleType::T_, {{RuleType::M, RuleType::F, RuleType::T_, }, {RuleType::_epsilon, }, }},
	{RuleType::V, {{RuleType::I, }, }},
};

static const std::map<RuleType, std::set<RuleType>> first{
	{RuleType::A, {RuleType::A, }},
	{RuleType::CompUnit, {RuleType::I, }},
	{RuleType::E, {RuleType::I, RuleType::LParen, }},
	{RuleType::E_, {RuleType::A, RuleType::_epsilon, }},
	{RuleType::Eq, {RuleType::Eq, }},
	{RuleType::F, {RuleType::I, RuleType::LParen, }},
	{RuleType::I, {RuleType::I, }},
	{RuleType::LParen, {RuleType::LParen, }},
	{RuleType::M, {RuleType::M, }},
	{RuleType::RParen, {RuleType::RParen, }},
	{RuleType::T, {RuleType::I, RuleType::LParen, }},
	{RuleType::T_, {RuleType::M, RuleType::_epsilon, }},
	{RuleType::V, {RuleType::I, }},
	{RuleType::_epsilon, {}},
};

static const std::map<RuleType, std::set<RuleType>> follow{
	{RuleType::A, {RuleType::I, RuleType::LParen, }},
	{RuleType::CompUnit, {RuleType::_end, }},
	{RuleType::E, {RuleType::RParen, RuleType::_end, }},
	{RuleType::E_, {RuleType::RParen, RuleType::_end, }},
	{RuleType::Eq, {RuleType::I, RuleType::LParen, }},
	{RuleType::F, {RuleType::A, RuleType::M, RuleType::RParen, RuleType::_end, }},
	{RuleType::I, {RuleType::A, RuleType::Eq, RuleType::M, RuleType::RParen, RuleType::_end, }},
	{RuleType::LParen, {RuleType::I, RuleType::LParen, }},
	{RuleType::M, {RuleType::I, RuleType::LParen, }},
	{RuleType::RParen, {RuleType::A, RuleType::M, RuleType::RParen, RuleType::_end, }},
	{RuleType::T, {RuleType::A, RuleType::RParen, RuleType::_end, }},
	{RuleType::T_, {RuleType::A, RuleType::RParen, RuleType::_end, }},
	{RuleType::V, {RuleType::Eq, }},
	{RuleType::_epsilon, {RuleType::A, RuleType::RParen, RuleType::_end, }},
};

static const std::map<
	RuleType, std::map<RuleType, std::pair<RuleType, std::vector<RuleType>>>
> table{
	{RuleType::CompUnit, {{RuleType::I, {RuleType::CompUnit, {RuleType::V, RuleType::Eq, RuleType::E, }}, }, }},
	{RuleType::E, {{RuleType::I, {RuleType::E, {RuleType::T, RuleType::E_, }}, }, {RuleType::LParen, {RuleType::E, {RuleType::T, RuleType::E_, }}, }, }},
	{RuleType::E_, {{RuleType::A, {RuleType::E_, {RuleType::A, RuleType::T, RuleType::E_, }}, }, {RuleType::RParen, {RuleType::E_, {RuleType::_epsilon, }}, }, {RuleType::_end, {RuleType::E_, {RuleType::_epsilon, }}, }, }},
	{RuleType::F, {{RuleType::I, {RuleType::F, {RuleType::I, }}, }, {RuleType::LParen, {RuleType::F, {RuleType::LParen, RuleType::E, RuleType::RParen, }}, }, }},
	{RuleType::T, {{RuleType::I, {RuleType::T, {RuleType::F, RuleType::T_, }}, }, {RuleType::LParen, {RuleType::T, {RuleType::F, RuleType::T_, }}, }, }},
	{RuleType::T_, {{RuleType::A, {RuleType::T_, {RuleType::_epsilon, }}, }, {RuleType::M, {RuleType::T_, {RuleType::M, RuleType::F, RuleType::T_, }}, }, {RuleType::RParen, {RuleType::T_, {RuleType::_epsilon, }}, }, {RuleType::_end, {RuleType::T_, {RuleType::_epsilon, }}, }, }},
	{RuleType::V, {{RuleType::I, {RuleType::V, {RuleType::I, }}, }, }},
};

static const std::set<RuleType> terms{
	RuleType::A,
	RuleType::Eq,
	RuleType::I,
	RuleType::LParen,
	RuleType::M,
	RuleType::RParen,
};

static const RuleType start = RuleType::CompUnit;

static const RuleType end = RuleType::_end;

static const RuleType epsilon = RuleType::_epsilon;

}
