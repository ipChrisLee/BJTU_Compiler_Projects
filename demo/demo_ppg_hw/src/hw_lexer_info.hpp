#pragma once
#include <map>
#include <set>
#include <cstdint>
#include <string>
#include <string_view>



namespace hw_lexer_info {
using NodeID_t = uint64_t;
enum class TokenType {
	BeginStmt, 
	ChD, 
	ChS, 
	ChSep, 
	EndStmt, 
	WS_Str, 
};

static std::set<TokenType> tokensToBeThrown {
	TokenType::WS_Str,
};
static std::string_view get_token_type_name(TokenType token) {
	switch (token) {
		case TokenType::BeginStmt:
			return "BeginStmt";
		case TokenType::ChD:
			return "ChD";
		case TokenType::ChS:
			return "ChS";
		case TokenType::ChSep:
			return "ChSep";
		case TokenType::EndStmt:
			return "EndStmt";
		case TokenType::WS_Str:
			return "WS_Str";
	}
}

static const std::map<NodeID_t, TokenType> nodeType{
	{105553180757112, TokenType::WS_Str},
	{105553180757208, TokenType::WS_Str},
	{105553180757304, TokenType::WS_Str},
	{105553180757400, TokenType::WS_Str},
	{105553180757496, TokenType::ChSep},
	{105553180757688, TokenType::ChD},
	{105553180757880, TokenType::ChS},
	{105553180757976, TokenType::WS_Str},
	{105553180758072, TokenType::WS_Str},
	{105553180758168, TokenType::WS_Str},
	{105553180758264, TokenType::WS_Str},
	{105553180758648, TokenType::EndStmt},
	{105553180758840, TokenType::BeginStmt},
};

static const std::map<NodeID_t, std::map<char, NodeID_t>> edges{
	{105553180757016, {{9, 0x600003d80c78},{10, 0x600003d80cd8},{13, 0x600003d80d38},{32, 0x600003d80d98},{59, 0x600003d80df8},{98, 0x600003d80e58},{100, 0x600003d80eb8},{101, 0x600003d80f18},{115, 0x600003d80f78},}},
	{105553180757112, {{9, 0x600003d80fd8},{10, 0x600003d81038},{13, 0x600003d81098},{32, 0x600003d810f8},}},
	{105553180757208, {{9, 0x600003d80fd8},{10, 0x600003d81038},{13, 0x600003d81098},{32, 0x600003d810f8},}},
	{105553180757304, {{9, 0x600003d80fd8},{10, 0x600003d81038},{13, 0x600003d81098},{32, 0x600003d810f8},}},
	{105553180757400, {{9, 0x600003d80fd8},{10, 0x600003d81038},{13, 0x600003d81098},{32, 0x600003d810f8},}},
	{105553180757496, {}},
	{105553180757592, {{101, 0x600003d81158},}},
	{105553180757688, {}},
	{105553180757784, {{110, 0x600003d811b8},}},
	{105553180757880, {}},
	{105553180757976, {{9, 0x600003d80fd8},{10, 0x600003d81038},{13, 0x600003d81098},{32, 0x600003d810f8},}},
	{105553180758072, {{9, 0x600003d80fd8},{10, 0x600003d81038},{13, 0x600003d81098},{32, 0x600003d810f8},}},
	{105553180758168, {{9, 0x600003d80fd8},{10, 0x600003d81038},{13, 0x600003d81098},{32, 0x600003d810f8},}},
	{105553180758264, {{9, 0x600003d80fd8},{10, 0x600003d81038},{13, 0x600003d81098},{32, 0x600003d810f8},}},
	{105553180758360, {{103, 0x600003d81218},}},
	{105553180758456, {{100, 0x600003d81278},}},
	{105553180758552, {{105, 0x600003d812d8},}},
	{105553180758648, {}},
	{105553180758744, {{110, 0x600003d81338},}},
	{105553180758840, {}},
};

static const NodeID_t start = 105553180757016;
}
