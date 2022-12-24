#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <set>
#include <utility>



namespace b_parser_info{
enum class RuleType {
	AddExp,
	BasicType,
	BlockContent,
	BlockItem,
	CompUnit,
	ConstExp,
	Decl,
	Exp,
	LAndExp,
	LEqExp,
	LOrExp,
	LRelExp,
	MulExp,
	PrimaryExp,
	Stmt,
	UnaryExp,
	Val,
	VarType,
	idName,
	keyBreak,
	keyContinue,
	keyDo,
	keyElse,
	keyFloat,
	keyFor,
	keyIf,
	keyInt,
	keyReturn,
	keyVoid,
	keyWhile,
	literalInt,
	opAdd,
	opAssign,
	opBang,
	opDiv,
	opEq,
	opGe,
	opGt,
	opLAnd,
	opLOr,
	opLe,
	opLt,
	opMinus,
	opMod,
	opMul,
	opNeq,
	sepColon,
	sepLCBrkt,
	sepLParen,
	sepLSBrkt,
	sepRCBrkt,
	sepRParen,
	sepRSBrkt,
	sepSemicolon,
	_epsilon,
	_end,
};

static RuleType strToRuleType(std::string_view str) {
	if (str.empty()) {
		std::cerr << "Input string is empty!" << std::endl;
		exit(-1);
	} else if (str == "AddExp") {
		return RuleType::AddExp;
	} else if (str == "BasicType") {
		return RuleType::BasicType;
	} else if (str == "BlockContent") {
		return RuleType::BlockContent;
	} else if (str == "BlockItem") {
		return RuleType::BlockItem;
	} else if (str == "CompUnit") {
		return RuleType::CompUnit;
	} else if (str == "ConstExp") {
		return RuleType::ConstExp;
	} else if (str == "Decl") {
		return RuleType::Decl;
	} else if (str == "Exp") {
		return RuleType::Exp;
	} else if (str == "LAndExp") {
		return RuleType::LAndExp;
	} else if (str == "LEqExp") {
		return RuleType::LEqExp;
	} else if (str == "LOrExp") {
		return RuleType::LOrExp;
	} else if (str == "LRelExp") {
		return RuleType::LRelExp;
	} else if (str == "MulExp") {
		return RuleType::MulExp;
	} else if (str == "PrimaryExp") {
		return RuleType::PrimaryExp;
	} else if (str == "Stmt") {
		return RuleType::Stmt;
	} else if (str == "UnaryExp") {
		return RuleType::UnaryExp;
	} else if (str == "Val") {
		return RuleType::Val;
	} else if (str == "VarType") {
		return RuleType::VarType;
	} else if (str == "idName") {
		return RuleType::idName;
	} else if (str == "keyBreak") {
		return RuleType::keyBreak;
	} else if (str == "keyContinue") {
		return RuleType::keyContinue;
	} else if (str == "keyDo") {
		return RuleType::keyDo;
	} else if (str == "keyElse") {
		return RuleType::keyElse;
	} else if (str == "keyFloat") {
		return RuleType::keyFloat;
	} else if (str == "keyFor") {
		return RuleType::keyFor;
	} else if (str == "keyIf") {
		return RuleType::keyIf;
	} else if (str == "keyInt") {
		return RuleType::keyInt;
	} else if (str == "keyReturn") {
		return RuleType::keyReturn;
	} else if (str == "keyVoid") {
		return RuleType::keyVoid;
	} else if (str == "keyWhile") {
		return RuleType::keyWhile;
	} else if (str == "literalInt") {
		return RuleType::literalInt;
	} else if (str == "opAdd") {
		return RuleType::opAdd;
	} else if (str == "opAssign") {
		return RuleType::opAssign;
	} else if (str == "opBang") {
		return RuleType::opBang;
	} else if (str == "opDiv") {
		return RuleType::opDiv;
	} else if (str == "opEq") {
		return RuleType::opEq;
	} else if (str == "opGe") {
		return RuleType::opGe;
	} else if (str == "opGt") {
		return RuleType::opGt;
	} else if (str == "opLAnd") {
		return RuleType::opLAnd;
	} else if (str == "opLOr") {
		return RuleType::opLOr;
	} else if (str == "opLe") {
		return RuleType::opLe;
	} else if (str == "opLt") {
		return RuleType::opLt;
	} else if (str == "opMinus") {
		return RuleType::opMinus;
	} else if (str == "opMod") {
		return RuleType::opMod;
	} else if (str == "opMul") {
		return RuleType::opMul;
	} else if (str == "opNeq") {
		return RuleType::opNeq;
	} else if (str == "sepColon") {
		return RuleType::sepColon;
	} else if (str == "sepLCBrkt") {
		return RuleType::sepLCBrkt;
	} else if (str == "sepLParen") {
		return RuleType::sepLParen;
	} else if (str == "sepLSBrkt") {
		return RuleType::sepLSBrkt;
	} else if (str == "sepRCBrkt") {
		return RuleType::sepRCBrkt;
	} else if (str == "sepRParen") {
		return RuleType::sepRParen;
	} else if (str == "sepRSBrkt") {
		return RuleType::sepRSBrkt;
	} else if (str == "sepSemicolon") {
		return RuleType::sepSemicolon;
	} else if (str == "_epsilon") {
		return RuleType::_epsilon;
	} else if (str == "_end") {
		return RuleType::_end;
	} else {
		std::cerr << "Unknown rule name [" << str << "]." << std::endl;
		exit(-1);
	}
}

static std::string ruleTypeToStr(RuleType ruleType) {
	if (0) {
	} else if (ruleType == RuleType::AddExp) {
		return "AddExp";
	} else if (ruleType == RuleType::BasicType) {
		return "BasicType";
	} else if (ruleType == RuleType::BlockContent) {
		return "BlockContent";
	} else if (ruleType == RuleType::BlockItem) {
		return "BlockItem";
	} else if (ruleType == RuleType::CompUnit) {
		return "CompUnit";
	} else if (ruleType == RuleType::ConstExp) {
		return "ConstExp";
	} else if (ruleType == RuleType::Decl) {
		return "Decl";
	} else if (ruleType == RuleType::Exp) {
		return "Exp";
	} else if (ruleType == RuleType::LAndExp) {
		return "LAndExp";
	} else if (ruleType == RuleType::LEqExp) {
		return "LEqExp";
	} else if (ruleType == RuleType::LOrExp) {
		return "LOrExp";
	} else if (ruleType == RuleType::LRelExp) {
		return "LRelExp";
	} else if (ruleType == RuleType::MulExp) {
		return "MulExp";
	} else if (ruleType == RuleType::PrimaryExp) {
		return "PrimaryExp";
	} else if (ruleType == RuleType::Stmt) {
		return "Stmt";
	} else if (ruleType == RuleType::UnaryExp) {
		return "UnaryExp";
	} else if (ruleType == RuleType::Val) {
		return "Val";
	} else if (ruleType == RuleType::VarType) {
		return "VarType";
	} else if (ruleType == RuleType::idName) {
		return "idName";
	} else if (ruleType == RuleType::keyBreak) {
		return "keyBreak";
	} else if (ruleType == RuleType::keyContinue) {
		return "keyContinue";
	} else if (ruleType == RuleType::keyDo) {
		return "keyDo";
	} else if (ruleType == RuleType::keyElse) {
		return "keyElse";
	} else if (ruleType == RuleType::keyFloat) {
		return "keyFloat";
	} else if (ruleType == RuleType::keyFor) {
		return "keyFor";
	} else if (ruleType == RuleType::keyIf) {
		return "keyIf";
	} else if (ruleType == RuleType::keyInt) {
		return "keyInt";
	} else if (ruleType == RuleType::keyReturn) {
		return "keyReturn";
	} else if (ruleType == RuleType::keyVoid) {
		return "keyVoid";
	} else if (ruleType == RuleType::keyWhile) {
		return "keyWhile";
	} else if (ruleType == RuleType::literalInt) {
		return "literalInt";
	} else if (ruleType == RuleType::opAdd) {
		return "opAdd";
	} else if (ruleType == RuleType::opAssign) {
		return "opAssign";
	} else if (ruleType == RuleType::opBang) {
		return "opBang";
	} else if (ruleType == RuleType::opDiv) {
		return "opDiv";
	} else if (ruleType == RuleType::opEq) {
		return "opEq";
	} else if (ruleType == RuleType::opGe) {
		return "opGe";
	} else if (ruleType == RuleType::opGt) {
		return "opGt";
	} else if (ruleType == RuleType::opLAnd) {
		return "opLAnd";
	} else if (ruleType == RuleType::opLOr) {
		return "opLOr";
	} else if (ruleType == RuleType::opLe) {
		return "opLe";
	} else if (ruleType == RuleType::opLt) {
		return "opLt";
	} else if (ruleType == RuleType::opMinus) {
		return "opMinus";
	} else if (ruleType == RuleType::opMod) {
		return "opMod";
	} else if (ruleType == RuleType::opMul) {
		return "opMul";
	} else if (ruleType == RuleType::opNeq) {
		return "opNeq";
	} else if (ruleType == RuleType::sepColon) {
		return "sepColon";
	} else if (ruleType == RuleType::sepLCBrkt) {
		return "sepLCBrkt";
	} else if (ruleType == RuleType::sepLParen) {
		return "sepLParen";
	} else if (ruleType == RuleType::sepLSBrkt) {
		return "sepLSBrkt";
	} else if (ruleType == RuleType::sepRCBrkt) {
		return "sepRCBrkt";
	} else if (ruleType == RuleType::sepRParen) {
		return "sepRParen";
	} else if (ruleType == RuleType::sepRSBrkt) {
		return "sepRSBrkt";
	} else if (ruleType == RuleType::sepSemicolon) {
		return "sepSemicolon";
	} else if (ruleType == RuleType::_epsilon) {
		return "_epsilon";
	} else if (ruleType == RuleType::_end) {
		return "_end";
	} else {
		std::cerr << "Unknown rule type." << std::endl;
		exit(-1);
	}
}
enum class ParseType {
	add_exp_add,
	add_exp_flow,
	add_exp_sub,
	basic_type_float,
	basic_type_int,
	block_content_body,
	block_content_last,
	block_item_block,
	block_item_break,
	block_item_continue,
	block_item_decl,
	block_item_if,
	block_item_return,
	block_item_stmt,
	block_item_while,
	comp_unit,
	const_exp,
	decl,
	exp,
	l_and_exp_flow,
	l_and_exp_main,
	l_eq_exp_eq,
	l_eq_exp_flow,
	l_eq_exp_neq,
	l_or_exp_flow,
	l_or_exp_main,
	l_rel_exp_flow,
	l_rel_exp_ge,
	l_rel_exp_gt,
	l_rel_exp_le,
	l_rel_exp_lt,
	mul_exp_div,
	mul_exp_flow,
	mul_exp_mod,
	mul_exp_mul,
	primary_exp_literal_int,
	primary_exp_paren_exp,
	primary_exp_r_val,
	stmt_assign,
	stmt_exp,
	unary_exp_flow,
	unary_exp_neg,
	unary_exp_not,
	unary_exp_pos,
	l_val_indexed_var,
	l_val_var,
	var_type_array,
	var_type_basic,
};

static ParseType strToParseType(std::string_view str) {
	if (0) {
	} else if (str == "add_exp_add") {
		return ParseType::add_exp_add;
	} else if (str == "add_exp_flow") {
		return ParseType::add_exp_flow;
	} else if (str == "add_exp_sub") {
		return ParseType::add_exp_sub;
	} else if (str == "basic_type_float") {
		return ParseType::basic_type_float;
	} else if (str == "basic_type_int") {
		return ParseType::basic_type_int;
	} else if (str == "block_content_body") {
		return ParseType::block_content_body;
	} else if (str == "block_content_last") {
		return ParseType::block_content_last;
	} else if (str == "block_item_block") {
		return ParseType::block_item_block;
	} else if (str == "block_item_break") {
		return ParseType::block_item_break;
	} else if (str == "block_item_continue") {
		return ParseType::block_item_continue;
	} else if (str == "block_item_decl") {
		return ParseType::block_item_decl;
	} else if (str == "block_item_if") {
		return ParseType::block_item_if;
	} else if (str == "block_item_return") {
		return ParseType::block_item_return;
	} else if (str == "block_item_stmt") {
		return ParseType::block_item_stmt;
	} else if (str == "block_item_while") {
		return ParseType::block_item_while;
	} else if (str == "comp_unit") {
		return ParseType::comp_unit;
	} else if (str == "const_exp") {
		return ParseType::const_exp;
	} else if (str == "decl") {
		return ParseType::decl;
	} else if (str == "exp") {
		return ParseType::exp;
	} else if (str == "l_and_exp_flow") {
		return ParseType::l_and_exp_flow;
	} else if (str == "l_and_exp_main") {
		return ParseType::l_and_exp_main;
	} else if (str == "l_eq_exp_eq") {
		return ParseType::l_eq_exp_eq;
	} else if (str == "l_eq_exp_flow") {
		return ParseType::l_eq_exp_flow;
	} else if (str == "l_eq_exp_neq") {
		return ParseType::l_eq_exp_neq;
	} else if (str == "l_or_exp_flow") {
		return ParseType::l_or_exp_flow;
	} else if (str == "l_or_exp_main") {
		return ParseType::l_or_exp_main;
	} else if (str == "l_rel_exp_flow") {
		return ParseType::l_rel_exp_flow;
	} else if (str == "l_rel_exp_ge") {
		return ParseType::l_rel_exp_ge;
	} else if (str == "l_rel_exp_gt") {
		return ParseType::l_rel_exp_gt;
	} else if (str == "l_rel_exp_le") {
		return ParseType::l_rel_exp_le;
	} else if (str == "l_rel_exp_lt") {
		return ParseType::l_rel_exp_lt;
	} else if (str == "mul_exp_div") {
		return ParseType::mul_exp_div;
	} else if (str == "mul_exp_flow") {
		return ParseType::mul_exp_flow;
	} else if (str == "mul_exp_mod") {
		return ParseType::mul_exp_mod;
	} else if (str == "mul_exp_mul") {
		return ParseType::mul_exp_mul;
	} else if (str == "primary_exp_literal_int") {
		return ParseType::primary_exp_literal_int;
	} else if (str == "primary_exp_paren_exp") {
		return ParseType::primary_exp_paren_exp;
	} else if (str == "primary_exp_r_val") {
		return ParseType::primary_exp_r_val;
	} else if (str == "stmt_assign") {
		return ParseType::stmt_assign;
	} else if (str == "stmt_exp") {
		return ParseType::stmt_exp;
	} else if (str == "unary_exp_flow") {
		return ParseType::unary_exp_flow;
	} else if (str == "unary_exp_neg") {
		return ParseType::unary_exp_neg;
	} else if (str == "unary_exp_not") {
		return ParseType::unary_exp_not;
	} else if (str == "unary_exp_pos") {
		return ParseType::unary_exp_pos;
	} else if (str == "l_val_indexed_var") {
		return ParseType::l_val_indexed_var;
	} else if (str == "l_val_var") {
		return ParseType::l_val_var;
	} else if (str == "var_type_array") {
		return ParseType::var_type_array;
	} else if (str == "var_type_basic") {
		return ParseType::var_type_basic;
	} else {
		std::cerr << "Unknown parse type name [" << str << "]." << std::endl;
		exit(-1);
	}
}

static std::string parseTypeToStr(ParseType parseType) {
	if (0) {
	} else if (parseType == ParseType::add_exp_add) {
		return "add_exp_add";
	} else if (parseType == ParseType::add_exp_flow) {
		return "add_exp_flow";
	} else if (parseType == ParseType::add_exp_sub) {
		return "add_exp_sub";
	} else if (parseType == ParseType::basic_type_float) {
		return "basic_type_float";
	} else if (parseType == ParseType::basic_type_int) {
		return "basic_type_int";
	} else if (parseType == ParseType::block_content_body) {
		return "block_content_body";
	} else if (parseType == ParseType::block_content_last) {
		return "block_content_last";
	} else if (parseType == ParseType::block_item_block) {
		return "block_item_block";
	} else if (parseType == ParseType::block_item_break) {
		return "block_item_break";
	} else if (parseType == ParseType::block_item_continue) {
		return "block_item_continue";
	} else if (parseType == ParseType::block_item_decl) {
		return "block_item_decl";
	} else if (parseType == ParseType::block_item_if) {
		return "block_item_if";
	} else if (parseType == ParseType::block_item_return) {
		return "block_item_return";
	} else if (parseType == ParseType::block_item_stmt) {
		return "block_item_stmt";
	} else if (parseType == ParseType::block_item_while) {
		return "block_item_while";
	} else if (parseType == ParseType::comp_unit) {
		return "comp_unit";
	} else if (parseType == ParseType::const_exp) {
		return "const_exp";
	} else if (parseType == ParseType::decl) {
		return "decl";
	} else if (parseType == ParseType::exp) {
		return "exp";
	} else if (parseType == ParseType::l_and_exp_flow) {
		return "l_and_exp_flow";
	} else if (parseType == ParseType::l_and_exp_main) {
		return "l_and_exp_main";
	} else if (parseType == ParseType::l_eq_exp_eq) {
		return "l_eq_exp_eq";
	} else if (parseType == ParseType::l_eq_exp_flow) {
		return "l_eq_exp_flow";
	} else if (parseType == ParseType::l_eq_exp_neq) {
		return "l_eq_exp_neq";
	} else if (parseType == ParseType::l_or_exp_flow) {
		return "l_or_exp_flow";
	} else if (parseType == ParseType::l_or_exp_main) {
		return "l_or_exp_main";
	} else if (parseType == ParseType::l_rel_exp_flow) {
		return "l_rel_exp_flow";
	} else if (parseType == ParseType::l_rel_exp_ge) {
		return "l_rel_exp_ge";
	} else if (parseType == ParseType::l_rel_exp_gt) {
		return "l_rel_exp_gt";
	} else if (parseType == ParseType::l_rel_exp_le) {
		return "l_rel_exp_le";
	} else if (parseType == ParseType::l_rel_exp_lt) {
		return "l_rel_exp_lt";
	} else if (parseType == ParseType::mul_exp_div) {
		return "mul_exp_div";
	} else if (parseType == ParseType::mul_exp_flow) {
		return "mul_exp_flow";
	} else if (parseType == ParseType::mul_exp_mod) {
		return "mul_exp_mod";
	} else if (parseType == ParseType::mul_exp_mul) {
		return "mul_exp_mul";
	} else if (parseType == ParseType::primary_exp_literal_int) {
		return "primary_exp_literal_int";
	} else if (parseType == ParseType::primary_exp_paren_exp) {
		return "primary_exp_paren_exp";
	} else if (parseType == ParseType::primary_exp_r_val) {
		return "primary_exp_r_val";
	} else if (parseType == ParseType::stmt_assign) {
		return "stmt_assign";
	} else if (parseType == ParseType::stmt_exp) {
		return "stmt_exp";
	} else if (parseType == ParseType::unary_exp_flow) {
		return "unary_exp_flow";
	} else if (parseType == ParseType::unary_exp_neg) {
		return "unary_exp_neg";
	} else if (parseType == ParseType::unary_exp_not) {
		return "unary_exp_not";
	} else if (parseType == ParseType::unary_exp_pos) {
		return "unary_exp_pos";
	} else if (parseType == ParseType::l_val_indexed_var) {
		return "l_val_indexed_var";
	} else if (parseType == ParseType::l_val_var) {
		return "l_val_var";
	} else if (parseType == ParseType::var_type_array) {
		return "var_type_array";
	} else if (parseType == ParseType::var_type_basic) {
		return "var_type_basic";
	} else {
		std::cerr << "Unknown rule type." << std::endl;
		exit(-1);
	}
}

using NodeID_t = uint64_t;
static std::map<NodeID_t, std::map<RuleType, NodeID_t>> actionTableS = {
	{0, {{RuleType::idName, 17}, {RuleType::keyBreak, 18}, {RuleType::keyContinue, 19}, {RuleType::keyFloat, 20}, {RuleType::keyIf, 21}, {RuleType::keyInt, 22}, {RuleType::keyReturn, 23}, {RuleType::keyWhile, 24}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLCBrkt, 29}, {RuleType::sepLParen, 30}, }},
	{1, {{RuleType::opAdd, 31}, {RuleType::opMinus, 32}, }},
	{2, {{RuleType::sepLSBrkt, 33}, }},
	{4, {{RuleType::idName, 17}, {RuleType::keyBreak, 18}, {RuleType::keyContinue, 19}, {RuleType::keyFloat, 20}, {RuleType::keyIf, 21}, {RuleType::keyInt, 22}, {RuleType::keyReturn, 23}, {RuleType::keyWhile, 24}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLCBrkt, 29}, {RuleType::sepLParen, 30}, }},
	{5, {{RuleType::sepSemicolon, 35}, }},
	{7, {{RuleType::opLAnd, 36}, }},
	{8, {{RuleType::opEq, 37}, {RuleType::opNeq, 38}, }},
	{9, {{RuleType::opLOr, 39}, }},
	{10, {{RuleType::opGe, 40}, {RuleType::opGt, 41}, {RuleType::opLe, 42}, {RuleType::opLt, 43}, }},
	{11, {{RuleType::opDiv, 44}, {RuleType::opMod, 45}, {RuleType::opMul, 46}, }},
	{13, {{RuleType::sepSemicolon, 47}, }},
	{15, {{RuleType::opAssign, 48}, }},
	{16, {{RuleType::idName, 49}, }},
	{17, {{RuleType::sepLSBrkt, 50}, }},
	{18, {{RuleType::sepSemicolon, 51}, }},
	{19, {{RuleType::sepSemicolon, 52}, }},
	{21, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{23, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{24, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{26, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{27, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{28, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{29, {{RuleType::idName, 17}, {RuleType::keyBreak, 18}, {RuleType::keyContinue, 19}, {RuleType::keyFloat, 20}, {RuleType::keyIf, 21}, {RuleType::keyInt, 22}, {RuleType::keyReturn, 23}, {RuleType::keyWhile, 24}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLCBrkt, 29}, {RuleType::sepLParen, 30}, }},
	{30, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{31, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{32, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{33, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{36, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{37, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{38, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{39, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{40, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{41, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{42, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{43, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{44, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{45, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{46, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{48, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{50, {{RuleType::idName, 17}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLParen, 30}, }},
	{53, {{RuleType::sepColon, 79}, }},
	{55, {{RuleType::sepSemicolon, 80}, }},
	{56, {{RuleType::sepColon, 81}, }},
	{60, {{RuleType::sepRCBrkt, 82}, }},
	{61, {{RuleType::sepRParen, 83}, }},
	{62, {{RuleType::opDiv, 44}, {RuleType::opMod, 45}, {RuleType::opMul, 46}, }},
	{63, {{RuleType::opDiv, 44}, {RuleType::opMod, 45}, {RuleType::opMul, 46}, }},
	{64, {{RuleType::opAdd, 31}, {RuleType::opMinus, 32}, }},
	{65, {{RuleType::sepRSBrkt, 84}, }},
	{66, {{RuleType::opEq, 37}, {RuleType::opNeq, 38}, }},
	{67, {{RuleType::opGe, 40}, {RuleType::opGt, 41}, {RuleType::opLe, 42}, {RuleType::opLt, 43}, }},
	{68, {{RuleType::opGe, 40}, {RuleType::opGt, 41}, {RuleType::opLe, 42}, {RuleType::opLt, 43}, }},
	{69, {{RuleType::opLAnd, 36}, }},
	{70, {{RuleType::opAdd, 31}, {RuleType::opMinus, 32}, }},
	{71, {{RuleType::opAdd, 31}, {RuleType::opMinus, 32}, }},
	{72, {{RuleType::opAdd, 31}, {RuleType::opMinus, 32}, }},
	{73, {{RuleType::opAdd, 31}, {RuleType::opMinus, 32}, }},
	{78, {{RuleType::sepRSBrkt, 85}, }},
	{79, {{RuleType::idName, 17}, {RuleType::keyBreak, 18}, {RuleType::keyContinue, 19}, {RuleType::keyFloat, 20}, {RuleType::keyIf, 21}, {RuleType::keyInt, 22}, {RuleType::keyReturn, 23}, {RuleType::keyWhile, 24}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLCBrkt, 29}, {RuleType::sepLParen, 30}, }},
	{81, {{RuleType::idName, 17}, {RuleType::keyBreak, 18}, {RuleType::keyContinue, 19}, {RuleType::keyFloat, 20}, {RuleType::keyIf, 21}, {RuleType::keyInt, 22}, {RuleType::keyReturn, 23}, {RuleType::keyWhile, 24}, {RuleType::literalInt, 25}, {RuleType::opAdd, 26}, {RuleType::opBang, 27}, {RuleType::opMinus, 28}, {RuleType::sepLCBrkt, 29}, {RuleType::sepLParen, 30}, }},
};
static std::map<NodeID_t, std::map<RuleType, NodeID_t>> actionTableG = {
	{0, {{RuleType::AddExp, 1}, {RuleType::BasicType, 2}, {RuleType::BlockContent, 3}, {RuleType::BlockItem, 4}, {RuleType::Decl, 5}, {RuleType::Exp, 6}, {RuleType::LAndExp, 7}, {RuleType::LEqExp, 8}, {RuleType::LOrExp, 9}, {RuleType::LRelExp, 10}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::Stmt, 13}, {RuleType::UnaryExp, 14}, {RuleType::Val, 15}, {RuleType::VarType, 16}, }},
	{4, {{RuleType::AddExp, 1}, {RuleType::BasicType, 2}, {RuleType::BlockContent, 34}, {RuleType::BlockItem, 4}, {RuleType::Decl, 5}, {RuleType::Exp, 6}, {RuleType::LAndExp, 7}, {RuleType::LEqExp, 8}, {RuleType::LOrExp, 9}, {RuleType::LRelExp, 10}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::Stmt, 13}, {RuleType::UnaryExp, 14}, {RuleType::Val, 15}, {RuleType::VarType, 16}, }},
	{21, {{RuleType::AddExp, 1}, {RuleType::Exp, 53}, {RuleType::LAndExp, 7}, {RuleType::LEqExp, 8}, {RuleType::LOrExp, 9}, {RuleType::LRelExp, 10}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{23, {{RuleType::AddExp, 1}, {RuleType::Exp, 55}, {RuleType::LAndExp, 7}, {RuleType::LEqExp, 8}, {RuleType::LOrExp, 9}, {RuleType::LRelExp, 10}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{24, {{RuleType::AddExp, 1}, {RuleType::Exp, 56}, {RuleType::LAndExp, 7}, {RuleType::LEqExp, 8}, {RuleType::LOrExp, 9}, {RuleType::LRelExp, 10}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{26, {{RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 57}, {RuleType::Val, 54}, }},
	{27, {{RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 58}, {RuleType::Val, 54}, }},
	{28, {{RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 59}, {RuleType::Val, 54}, }},
	{29, {{RuleType::AddExp, 1}, {RuleType::BasicType, 2}, {RuleType::BlockContent, 60}, {RuleType::BlockItem, 4}, {RuleType::Decl, 5}, {RuleType::Exp, 6}, {RuleType::LAndExp, 7}, {RuleType::LEqExp, 8}, {RuleType::LOrExp, 9}, {RuleType::LRelExp, 10}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::Stmt, 13}, {RuleType::UnaryExp, 14}, {RuleType::Val, 15}, {RuleType::VarType, 16}, }},
	{30, {{RuleType::AddExp, 1}, {RuleType::Exp, 61}, {RuleType::LAndExp, 7}, {RuleType::LEqExp, 8}, {RuleType::LOrExp, 9}, {RuleType::LRelExp, 10}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{31, {{RuleType::MulExp, 62}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{32, {{RuleType::MulExp, 63}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{33, {{RuleType::AddExp, 64}, {RuleType::ConstExp, 65}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{36, {{RuleType::AddExp, 1}, {RuleType::LEqExp, 66}, {RuleType::LRelExp, 10}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{37, {{RuleType::AddExp, 1}, {RuleType::LRelExp, 67}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{38, {{RuleType::AddExp, 1}, {RuleType::LRelExp, 68}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{39, {{RuleType::AddExp, 1}, {RuleType::LAndExp, 69}, {RuleType::LEqExp, 8}, {RuleType::LRelExp, 10}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{40, {{RuleType::AddExp, 70}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{41, {{RuleType::AddExp, 71}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{42, {{RuleType::AddExp, 72}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{43, {{RuleType::AddExp, 73}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{44, {{RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 74}, {RuleType::Val, 54}, }},
	{45, {{RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 75}, {RuleType::Val, 54}, }},
	{46, {{RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 76}, {RuleType::Val, 54}, }},
	{48, {{RuleType::AddExp, 1}, {RuleType::Exp, 77}, {RuleType::LAndExp, 7}, {RuleType::LEqExp, 8}, {RuleType::LOrExp, 9}, {RuleType::LRelExp, 10}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{50, {{RuleType::AddExp, 1}, {RuleType::Exp, 78}, {RuleType::LAndExp, 7}, {RuleType::LEqExp, 8}, {RuleType::LOrExp, 9}, {RuleType::LRelExp, 10}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::UnaryExp, 14}, {RuleType::Val, 54}, }},
	{79, {{RuleType::AddExp, 1}, {RuleType::BasicType, 2}, {RuleType::BlockItem, 86}, {RuleType::Decl, 5}, {RuleType::Exp, 6}, {RuleType::LAndExp, 7}, {RuleType::LEqExp, 8}, {RuleType::LOrExp, 9}, {RuleType::LRelExp, 10}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::Stmt, 13}, {RuleType::UnaryExp, 14}, {RuleType::Val, 15}, {RuleType::VarType, 16}, }},
	{81, {{RuleType::AddExp, 1}, {RuleType::BasicType, 2}, {RuleType::BlockItem, 87}, {RuleType::Decl, 5}, {RuleType::Exp, 6}, {RuleType::LAndExp, 7}, {RuleType::LEqExp, 8}, {RuleType::LOrExp, 9}, {RuleType::LRelExp, 10}, {RuleType::MulExp, 11}, {RuleType::PrimaryExp, 12}, {RuleType::Stmt, 13}, {RuleType::UnaryExp, 14}, {RuleType::Val, 15}, {RuleType::VarType, 16}, }},
};
static std::map<NodeID_t, std::map<RuleType, ParseType>> actionTableR = {
	{1, {{RuleType::opEq, ParseType::l_rel_exp_flow}, {RuleType::opGe, ParseType::l_rel_exp_flow}, {RuleType::opGt, ParseType::l_rel_exp_flow}, {RuleType::opLAnd, ParseType::l_rel_exp_flow}, {RuleType::opLOr, ParseType::l_rel_exp_flow}, {RuleType::opLe, ParseType::l_rel_exp_flow}, {RuleType::opLt, ParseType::l_rel_exp_flow}, {RuleType::opNeq, ParseType::l_rel_exp_flow}, {RuleType::sepColon, ParseType::l_rel_exp_flow}, {RuleType::sepRParen, ParseType::l_rel_exp_flow}, {RuleType::sepRSBrkt, ParseType::l_rel_exp_flow}, {RuleType::sepSemicolon, ParseType::l_rel_exp_flow}, }},
	{2, {{RuleType::idName, ParseType::var_type_basic}, }},
	{4, {{RuleType::_end, ParseType::block_content_last}, {RuleType::sepRCBrkt, ParseType::block_content_last}, }},
	{6, {{RuleType::sepSemicolon, ParseType::stmt_exp}, }},
	{7, {{RuleType::opLOr, ParseType::l_or_exp_flow}, {RuleType::sepColon, ParseType::l_or_exp_flow}, {RuleType::sepRParen, ParseType::l_or_exp_flow}, {RuleType::sepRSBrkt, ParseType::l_or_exp_flow}, {RuleType::sepSemicolon, ParseType::l_or_exp_flow}, }},
	{8, {{RuleType::opLAnd, ParseType::l_and_exp_flow}, {RuleType::opLOr, ParseType::l_and_exp_flow}, {RuleType::sepColon, ParseType::l_and_exp_flow}, {RuleType::sepRParen, ParseType::l_and_exp_flow}, {RuleType::sepRSBrkt, ParseType::l_and_exp_flow}, {RuleType::sepSemicolon, ParseType::l_and_exp_flow}, }},
	{9, {{RuleType::sepColon, ParseType::exp}, {RuleType::sepRParen, ParseType::exp}, {RuleType::sepRSBrkt, ParseType::exp}, {RuleType::sepSemicolon, ParseType::exp}, }},
	{10, {{RuleType::opEq, ParseType::l_eq_exp_flow}, {RuleType::opLAnd, ParseType::l_eq_exp_flow}, {RuleType::opLOr, ParseType::l_eq_exp_flow}, {RuleType::opNeq, ParseType::l_eq_exp_flow}, {RuleType::sepColon, ParseType::l_eq_exp_flow}, {RuleType::sepRParen, ParseType::l_eq_exp_flow}, {RuleType::sepRSBrkt, ParseType::l_eq_exp_flow}, {RuleType::sepSemicolon, ParseType::l_eq_exp_flow}, }},
	{11, {{RuleType::opAdd, ParseType::add_exp_flow}, {RuleType::opEq, ParseType::add_exp_flow}, {RuleType::opGe, ParseType::add_exp_flow}, {RuleType::opGt, ParseType::add_exp_flow}, {RuleType::opLAnd, ParseType::add_exp_flow}, {RuleType::opLOr, ParseType::add_exp_flow}, {RuleType::opLe, ParseType::add_exp_flow}, {RuleType::opLt, ParseType::add_exp_flow}, {RuleType::opMinus, ParseType::add_exp_flow}, {RuleType::opNeq, ParseType::add_exp_flow}, {RuleType::sepColon, ParseType::add_exp_flow}, {RuleType::sepRParen, ParseType::add_exp_flow}, {RuleType::sepRSBrkt, ParseType::add_exp_flow}, {RuleType::sepSemicolon, ParseType::add_exp_flow}, }},
	{12, {{RuleType::opAdd, ParseType::unary_exp_flow}, {RuleType::opDiv, ParseType::unary_exp_flow}, {RuleType::opEq, ParseType::unary_exp_flow}, {RuleType::opGe, ParseType::unary_exp_flow}, {RuleType::opGt, ParseType::unary_exp_flow}, {RuleType::opLAnd, ParseType::unary_exp_flow}, {RuleType::opLOr, ParseType::unary_exp_flow}, {RuleType::opLe, ParseType::unary_exp_flow}, {RuleType::opLt, ParseType::unary_exp_flow}, {RuleType::opMinus, ParseType::unary_exp_flow}, {RuleType::opMod, ParseType::unary_exp_flow}, {RuleType::opMul, ParseType::unary_exp_flow}, {RuleType::opNeq, ParseType::unary_exp_flow}, {RuleType::sepColon, ParseType::unary_exp_flow}, {RuleType::sepRParen, ParseType::unary_exp_flow}, {RuleType::sepRSBrkt, ParseType::unary_exp_flow}, {RuleType::sepSemicolon, ParseType::unary_exp_flow}, }},
	{14, {{RuleType::opAdd, ParseType::mul_exp_flow}, {RuleType::opDiv, ParseType::mul_exp_flow}, {RuleType::opEq, ParseType::mul_exp_flow}, {RuleType::opGe, ParseType::mul_exp_flow}, {RuleType::opGt, ParseType::mul_exp_flow}, {RuleType::opLAnd, ParseType::mul_exp_flow}, {RuleType::opLOr, ParseType::mul_exp_flow}, {RuleType::opLe, ParseType::mul_exp_flow}, {RuleType::opLt, ParseType::mul_exp_flow}, {RuleType::opMinus, ParseType::mul_exp_flow}, {RuleType::opMod, ParseType::mul_exp_flow}, {RuleType::opMul, ParseType::mul_exp_flow}, {RuleType::opNeq, ParseType::mul_exp_flow}, {RuleType::sepColon, ParseType::mul_exp_flow}, {RuleType::sepRParen, ParseType::mul_exp_flow}, {RuleType::sepRSBrkt, ParseType::mul_exp_flow}, {RuleType::sepSemicolon, ParseType::mul_exp_flow}, }},
	{15, {{RuleType::opAdd, ParseType::primary_exp_r_val}, {RuleType::opDiv, ParseType::primary_exp_r_val}, {RuleType::opEq, ParseType::primary_exp_r_val}, {RuleType::opGe, ParseType::primary_exp_r_val}, {RuleType::opGt, ParseType::primary_exp_r_val}, {RuleType::opLAnd, ParseType::primary_exp_r_val}, {RuleType::opLOr, ParseType::primary_exp_r_val}, {RuleType::opLe, ParseType::primary_exp_r_val}, {RuleType::opLt, ParseType::primary_exp_r_val}, {RuleType::opMinus, ParseType::primary_exp_r_val}, {RuleType::opMod, ParseType::primary_exp_r_val}, {RuleType::opMul, ParseType::primary_exp_r_val}, {RuleType::opNeq, ParseType::primary_exp_r_val}, {RuleType::sepColon, ParseType::primary_exp_r_val}, {RuleType::sepRParen, ParseType::primary_exp_r_val}, {RuleType::sepRSBrkt, ParseType::primary_exp_r_val}, {RuleType::sepSemicolon, ParseType::primary_exp_r_val}, }},
	{17, {{RuleType::opAdd, ParseType::l_val_var}, {RuleType::opAssign, ParseType::l_val_var}, {RuleType::opDiv, ParseType::l_val_var}, {RuleType::opEq, ParseType::l_val_var}, {RuleType::opGe, ParseType::l_val_var}, {RuleType::opGt, ParseType::l_val_var}, {RuleType::opLAnd, ParseType::l_val_var}, {RuleType::opLOr, ParseType::l_val_var}, {RuleType::opLe, ParseType::l_val_var}, {RuleType::opLt, ParseType::l_val_var}, {RuleType::opMinus, ParseType::l_val_var}, {RuleType::opMod, ParseType::l_val_var}, {RuleType::opMul, ParseType::l_val_var}, {RuleType::opNeq, ParseType::l_val_var}, {RuleType::sepColon, ParseType::l_val_var}, {RuleType::sepRParen, ParseType::l_val_var}, {RuleType::sepRSBrkt, ParseType::l_val_var}, {RuleType::sepSemicolon, ParseType::l_val_var}, }},
	{20, {{RuleType::idName, ParseType::basic_type_float}, {RuleType::sepLSBrkt, ParseType::basic_type_float}, }},
	{22, {{RuleType::idName, ParseType::basic_type_int}, {RuleType::sepLSBrkt, ParseType::basic_type_int}, }},
	{25, {{RuleType::opAdd, ParseType::primary_exp_literal_int}, {RuleType::opDiv, ParseType::primary_exp_literal_int}, {RuleType::opEq, ParseType::primary_exp_literal_int}, {RuleType::opGe, ParseType::primary_exp_literal_int}, {RuleType::opGt, ParseType::primary_exp_literal_int}, {RuleType::opLAnd, ParseType::primary_exp_literal_int}, {RuleType::opLOr, ParseType::primary_exp_literal_int}, {RuleType::opLe, ParseType::primary_exp_literal_int}, {RuleType::opLt, ParseType::primary_exp_literal_int}, {RuleType::opMinus, ParseType::primary_exp_literal_int}, {RuleType::opMod, ParseType::primary_exp_literal_int}, {RuleType::opMul, ParseType::primary_exp_literal_int}, {RuleType::opNeq, ParseType::primary_exp_literal_int}, {RuleType::sepColon, ParseType::primary_exp_literal_int}, {RuleType::sepRParen, ParseType::primary_exp_literal_int}, {RuleType::sepRSBrkt, ParseType::primary_exp_literal_int}, {RuleType::sepSemicolon, ParseType::primary_exp_literal_int}, }},
	{34, {{RuleType::_end, ParseType::block_content_body}, {RuleType::sepRCBrkt, ParseType::block_content_body}, }},
	{35, {{RuleType::_end, ParseType::block_item_decl}, {RuleType::idName, ParseType::block_item_decl}, {RuleType::keyBreak, ParseType::block_item_decl}, {RuleType::keyContinue, ParseType::block_item_decl}, {RuleType::keyFloat, ParseType::block_item_decl}, {RuleType::keyIf, ParseType::block_item_decl}, {RuleType::keyInt, ParseType::block_item_decl}, {RuleType::keyReturn, ParseType::block_item_decl}, {RuleType::keyWhile, ParseType::block_item_decl}, {RuleType::literalInt, ParseType::block_item_decl}, {RuleType::opAdd, ParseType::block_item_decl}, {RuleType::opBang, ParseType::block_item_decl}, {RuleType::opMinus, ParseType::block_item_decl}, {RuleType::sepLCBrkt, ParseType::block_item_decl}, {RuleType::sepLParen, ParseType::block_item_decl}, {RuleType::sepRCBrkt, ParseType::block_item_decl}, }},
	{47, {{RuleType::_end, ParseType::block_item_stmt}, {RuleType::idName, ParseType::block_item_stmt}, {RuleType::keyBreak, ParseType::block_item_stmt}, {RuleType::keyContinue, ParseType::block_item_stmt}, {RuleType::keyFloat, ParseType::block_item_stmt}, {RuleType::keyIf, ParseType::block_item_stmt}, {RuleType::keyInt, ParseType::block_item_stmt}, {RuleType::keyReturn, ParseType::block_item_stmt}, {RuleType::keyWhile, ParseType::block_item_stmt}, {RuleType::literalInt, ParseType::block_item_stmt}, {RuleType::opAdd, ParseType::block_item_stmt}, {RuleType::opBang, ParseType::block_item_stmt}, {RuleType::opMinus, ParseType::block_item_stmt}, {RuleType::sepLCBrkt, ParseType::block_item_stmt}, {RuleType::sepLParen, ParseType::block_item_stmt}, {RuleType::sepRCBrkt, ParseType::block_item_stmt}, }},
	{49, {{RuleType::sepSemicolon, ParseType::decl}, }},
	{51, {{RuleType::_end, ParseType::block_item_break}, {RuleType::idName, ParseType::block_item_break}, {RuleType::keyBreak, ParseType::block_item_break}, {RuleType::keyContinue, ParseType::block_item_break}, {RuleType::keyFloat, ParseType::block_item_break}, {RuleType::keyIf, ParseType::block_item_break}, {RuleType::keyInt, ParseType::block_item_break}, {RuleType::keyReturn, ParseType::block_item_break}, {RuleType::keyWhile, ParseType::block_item_break}, {RuleType::literalInt, ParseType::block_item_break}, {RuleType::opAdd, ParseType::block_item_break}, {RuleType::opBang, ParseType::block_item_break}, {RuleType::opMinus, ParseType::block_item_break}, {RuleType::sepLCBrkt, ParseType::block_item_break}, {RuleType::sepLParen, ParseType::block_item_break}, {RuleType::sepRCBrkt, ParseType::block_item_break}, }},
	{52, {{RuleType::_end, ParseType::block_item_continue}, {RuleType::idName, ParseType::block_item_continue}, {RuleType::keyBreak, ParseType::block_item_continue}, {RuleType::keyContinue, ParseType::block_item_continue}, {RuleType::keyFloat, ParseType::block_item_continue}, {RuleType::keyIf, ParseType::block_item_continue}, {RuleType::keyInt, ParseType::block_item_continue}, {RuleType::keyReturn, ParseType::block_item_continue}, {RuleType::keyWhile, ParseType::block_item_continue}, {RuleType::literalInt, ParseType::block_item_continue}, {RuleType::opAdd, ParseType::block_item_continue}, {RuleType::opBang, ParseType::block_item_continue}, {RuleType::opMinus, ParseType::block_item_continue}, {RuleType::sepLCBrkt, ParseType::block_item_continue}, {RuleType::sepLParen, ParseType::block_item_continue}, {RuleType::sepRCBrkt, ParseType::block_item_continue}, }},
	{54, {{RuleType::opAdd, ParseType::primary_exp_r_val}, {RuleType::opDiv, ParseType::primary_exp_r_val}, {RuleType::opEq, ParseType::primary_exp_r_val}, {RuleType::opGe, ParseType::primary_exp_r_val}, {RuleType::opGt, ParseType::primary_exp_r_val}, {RuleType::opLAnd, ParseType::primary_exp_r_val}, {RuleType::opLOr, ParseType::primary_exp_r_val}, {RuleType::opLe, ParseType::primary_exp_r_val}, {RuleType::opLt, ParseType::primary_exp_r_val}, {RuleType::opMinus, ParseType::primary_exp_r_val}, {RuleType::opMod, ParseType::primary_exp_r_val}, {RuleType::opMul, ParseType::primary_exp_r_val}, {RuleType::opNeq, ParseType::primary_exp_r_val}, {RuleType::sepColon, ParseType::primary_exp_r_val}, {RuleType::sepRParen, ParseType::primary_exp_r_val}, {RuleType::sepRSBrkt, ParseType::primary_exp_r_val}, {RuleType::sepSemicolon, ParseType::primary_exp_r_val}, }},
	{57, {{RuleType::opAdd, ParseType::unary_exp_pos}, {RuleType::opDiv, ParseType::unary_exp_pos}, {RuleType::opEq, ParseType::unary_exp_pos}, {RuleType::opGe, ParseType::unary_exp_pos}, {RuleType::opGt, ParseType::unary_exp_pos}, {RuleType::opLAnd, ParseType::unary_exp_pos}, {RuleType::opLOr, ParseType::unary_exp_pos}, {RuleType::opLe, ParseType::unary_exp_pos}, {RuleType::opLt, ParseType::unary_exp_pos}, {RuleType::opMinus, ParseType::unary_exp_pos}, {RuleType::opMod, ParseType::unary_exp_pos}, {RuleType::opMul, ParseType::unary_exp_pos}, {RuleType::opNeq, ParseType::unary_exp_pos}, {RuleType::sepColon, ParseType::unary_exp_pos}, {RuleType::sepRParen, ParseType::unary_exp_pos}, {RuleType::sepRSBrkt, ParseType::unary_exp_pos}, {RuleType::sepSemicolon, ParseType::unary_exp_pos}, }},
	{58, {{RuleType::opAdd, ParseType::unary_exp_not}, {RuleType::opDiv, ParseType::unary_exp_not}, {RuleType::opEq, ParseType::unary_exp_not}, {RuleType::opGe, ParseType::unary_exp_not}, {RuleType::opGt, ParseType::unary_exp_not}, {RuleType::opLAnd, ParseType::unary_exp_not}, {RuleType::opLOr, ParseType::unary_exp_not}, {RuleType::opLe, ParseType::unary_exp_not}, {RuleType::opLt, ParseType::unary_exp_not}, {RuleType::opMinus, ParseType::unary_exp_not}, {RuleType::opMod, ParseType::unary_exp_not}, {RuleType::opMul, ParseType::unary_exp_not}, {RuleType::opNeq, ParseType::unary_exp_not}, {RuleType::sepColon, ParseType::unary_exp_not}, {RuleType::sepRParen, ParseType::unary_exp_not}, {RuleType::sepRSBrkt, ParseType::unary_exp_not}, {RuleType::sepSemicolon, ParseType::unary_exp_not}, }},
	{59, {{RuleType::opAdd, ParseType::unary_exp_neg}, {RuleType::opDiv, ParseType::unary_exp_neg}, {RuleType::opEq, ParseType::unary_exp_neg}, {RuleType::opGe, ParseType::unary_exp_neg}, {RuleType::opGt, ParseType::unary_exp_neg}, {RuleType::opLAnd, ParseType::unary_exp_neg}, {RuleType::opLOr, ParseType::unary_exp_neg}, {RuleType::opLe, ParseType::unary_exp_neg}, {RuleType::opLt, ParseType::unary_exp_neg}, {RuleType::opMinus, ParseType::unary_exp_neg}, {RuleType::opMod, ParseType::unary_exp_neg}, {RuleType::opMul, ParseType::unary_exp_neg}, {RuleType::opNeq, ParseType::unary_exp_neg}, {RuleType::sepColon, ParseType::unary_exp_neg}, {RuleType::sepRParen, ParseType::unary_exp_neg}, {RuleType::sepRSBrkt, ParseType::unary_exp_neg}, {RuleType::sepSemicolon, ParseType::unary_exp_neg}, }},
	{62, {{RuleType::opAdd, ParseType::add_exp_add}, {RuleType::opEq, ParseType::add_exp_add}, {RuleType::opGe, ParseType::add_exp_add}, {RuleType::opGt, ParseType::add_exp_add}, {RuleType::opLAnd, ParseType::add_exp_add}, {RuleType::opLOr, ParseType::add_exp_add}, {RuleType::opLe, ParseType::add_exp_add}, {RuleType::opLt, ParseType::add_exp_add}, {RuleType::opMinus, ParseType::add_exp_add}, {RuleType::opNeq, ParseType::add_exp_add}, {RuleType::sepColon, ParseType::add_exp_add}, {RuleType::sepRParen, ParseType::add_exp_add}, {RuleType::sepRSBrkt, ParseType::add_exp_add}, {RuleType::sepSemicolon, ParseType::add_exp_add}, }},
	{63, {{RuleType::opAdd, ParseType::add_exp_sub}, {RuleType::opEq, ParseType::add_exp_sub}, {RuleType::opGe, ParseType::add_exp_sub}, {RuleType::opGt, ParseType::add_exp_sub}, {RuleType::opLAnd, ParseType::add_exp_sub}, {RuleType::opLOr, ParseType::add_exp_sub}, {RuleType::opLe, ParseType::add_exp_sub}, {RuleType::opLt, ParseType::add_exp_sub}, {RuleType::opMinus, ParseType::add_exp_sub}, {RuleType::opNeq, ParseType::add_exp_sub}, {RuleType::sepColon, ParseType::add_exp_sub}, {RuleType::sepRParen, ParseType::add_exp_sub}, {RuleType::sepRSBrkt, ParseType::add_exp_sub}, {RuleType::sepSemicolon, ParseType::add_exp_sub}, }},
	{64, {{RuleType::sepRSBrkt, ParseType::const_exp}, }},
	{66, {{RuleType::opLAnd, ParseType::l_and_exp_main}, {RuleType::opLOr, ParseType::l_and_exp_main}, {RuleType::sepColon, ParseType::l_and_exp_main}, {RuleType::sepRParen, ParseType::l_and_exp_main}, {RuleType::sepRSBrkt, ParseType::l_and_exp_main}, {RuleType::sepSemicolon, ParseType::l_and_exp_main}, }},
	{67, {{RuleType::opEq, ParseType::l_eq_exp_eq}, {RuleType::opLAnd, ParseType::l_eq_exp_eq}, {RuleType::opLOr, ParseType::l_eq_exp_eq}, {RuleType::opNeq, ParseType::l_eq_exp_eq}, {RuleType::sepColon, ParseType::l_eq_exp_eq}, {RuleType::sepRParen, ParseType::l_eq_exp_eq}, {RuleType::sepRSBrkt, ParseType::l_eq_exp_eq}, {RuleType::sepSemicolon, ParseType::l_eq_exp_eq}, }},
	{68, {{RuleType::opEq, ParseType::l_eq_exp_neq}, {RuleType::opLAnd, ParseType::l_eq_exp_neq}, {RuleType::opLOr, ParseType::l_eq_exp_neq}, {RuleType::opNeq, ParseType::l_eq_exp_neq}, {RuleType::sepColon, ParseType::l_eq_exp_neq}, {RuleType::sepRParen, ParseType::l_eq_exp_neq}, {RuleType::sepRSBrkt, ParseType::l_eq_exp_neq}, {RuleType::sepSemicolon, ParseType::l_eq_exp_neq}, }},
	{69, {{RuleType::opLOr, ParseType::l_or_exp_main}, {RuleType::sepColon, ParseType::l_or_exp_main}, {RuleType::sepRParen, ParseType::l_or_exp_main}, {RuleType::sepRSBrkt, ParseType::l_or_exp_main}, {RuleType::sepSemicolon, ParseType::l_or_exp_main}, }},
	{70, {{RuleType::opEq, ParseType::l_rel_exp_ge}, {RuleType::opGe, ParseType::l_rel_exp_ge}, {RuleType::opGt, ParseType::l_rel_exp_ge}, {RuleType::opLAnd, ParseType::l_rel_exp_ge}, {RuleType::opLOr, ParseType::l_rel_exp_ge}, {RuleType::opLe, ParseType::l_rel_exp_ge}, {RuleType::opLt, ParseType::l_rel_exp_ge}, {RuleType::opNeq, ParseType::l_rel_exp_ge}, {RuleType::sepColon, ParseType::l_rel_exp_ge}, {RuleType::sepRParen, ParseType::l_rel_exp_ge}, {RuleType::sepRSBrkt, ParseType::l_rel_exp_ge}, {RuleType::sepSemicolon, ParseType::l_rel_exp_ge}, }},
	{71, {{RuleType::opEq, ParseType::l_rel_exp_gt}, {RuleType::opGe, ParseType::l_rel_exp_gt}, {RuleType::opGt, ParseType::l_rel_exp_gt}, {RuleType::opLAnd, ParseType::l_rel_exp_gt}, {RuleType::opLOr, ParseType::l_rel_exp_gt}, {RuleType::opLe, ParseType::l_rel_exp_gt}, {RuleType::opLt, ParseType::l_rel_exp_gt}, {RuleType::opNeq, ParseType::l_rel_exp_gt}, {RuleType::sepColon, ParseType::l_rel_exp_gt}, {RuleType::sepRParen, ParseType::l_rel_exp_gt}, {RuleType::sepRSBrkt, ParseType::l_rel_exp_gt}, {RuleType::sepSemicolon, ParseType::l_rel_exp_gt}, }},
	{72, {{RuleType::opEq, ParseType::l_rel_exp_le}, {RuleType::opGe, ParseType::l_rel_exp_le}, {RuleType::opGt, ParseType::l_rel_exp_le}, {RuleType::opLAnd, ParseType::l_rel_exp_le}, {RuleType::opLOr, ParseType::l_rel_exp_le}, {RuleType::opLe, ParseType::l_rel_exp_le}, {RuleType::opLt, ParseType::l_rel_exp_le}, {RuleType::opNeq, ParseType::l_rel_exp_le}, {RuleType::sepColon, ParseType::l_rel_exp_le}, {RuleType::sepRParen, ParseType::l_rel_exp_le}, {RuleType::sepRSBrkt, ParseType::l_rel_exp_le}, {RuleType::sepSemicolon, ParseType::l_rel_exp_le}, }},
	{73, {{RuleType::opEq, ParseType::l_rel_exp_lt}, {RuleType::opGe, ParseType::l_rel_exp_lt}, {RuleType::opGt, ParseType::l_rel_exp_lt}, {RuleType::opLAnd, ParseType::l_rel_exp_lt}, {RuleType::opLOr, ParseType::l_rel_exp_lt}, {RuleType::opLe, ParseType::l_rel_exp_lt}, {RuleType::opLt, ParseType::l_rel_exp_lt}, {RuleType::opNeq, ParseType::l_rel_exp_lt}, {RuleType::sepColon, ParseType::l_rel_exp_lt}, {RuleType::sepRParen, ParseType::l_rel_exp_lt}, {RuleType::sepRSBrkt, ParseType::l_rel_exp_lt}, {RuleType::sepSemicolon, ParseType::l_rel_exp_lt}, }},
	{74, {{RuleType::opAdd, ParseType::mul_exp_div}, {RuleType::opDiv, ParseType::mul_exp_div}, {RuleType::opEq, ParseType::mul_exp_div}, {RuleType::opGe, ParseType::mul_exp_div}, {RuleType::opGt, ParseType::mul_exp_div}, {RuleType::opLAnd, ParseType::mul_exp_div}, {RuleType::opLOr, ParseType::mul_exp_div}, {RuleType::opLe, ParseType::mul_exp_div}, {RuleType::opLt, ParseType::mul_exp_div}, {RuleType::opMinus, ParseType::mul_exp_div}, {RuleType::opMod, ParseType::mul_exp_div}, {RuleType::opMul, ParseType::mul_exp_div}, {RuleType::opNeq, ParseType::mul_exp_div}, {RuleType::sepColon, ParseType::mul_exp_div}, {RuleType::sepRParen, ParseType::mul_exp_div}, {RuleType::sepRSBrkt, ParseType::mul_exp_div}, {RuleType::sepSemicolon, ParseType::mul_exp_div}, }},
	{75, {{RuleType::opAdd, ParseType::mul_exp_mod}, {RuleType::opDiv, ParseType::mul_exp_mod}, {RuleType::opEq, ParseType::mul_exp_mod}, {RuleType::opGe, ParseType::mul_exp_mod}, {RuleType::opGt, ParseType::mul_exp_mod}, {RuleType::opLAnd, ParseType::mul_exp_mod}, {RuleType::opLOr, ParseType::mul_exp_mod}, {RuleType::opLe, ParseType::mul_exp_mod}, {RuleType::opLt, ParseType::mul_exp_mod}, {RuleType::opMinus, ParseType::mul_exp_mod}, {RuleType::opMod, ParseType::mul_exp_mod}, {RuleType::opMul, ParseType::mul_exp_mod}, {RuleType::opNeq, ParseType::mul_exp_mod}, {RuleType::sepColon, ParseType::mul_exp_mod}, {RuleType::sepRParen, ParseType::mul_exp_mod}, {RuleType::sepRSBrkt, ParseType::mul_exp_mod}, {RuleType::sepSemicolon, ParseType::mul_exp_mod}, }},
	{76, {{RuleType::opAdd, ParseType::mul_exp_mul}, {RuleType::opDiv, ParseType::mul_exp_mul}, {RuleType::opEq, ParseType::mul_exp_mul}, {RuleType::opGe, ParseType::mul_exp_mul}, {RuleType::opGt, ParseType::mul_exp_mul}, {RuleType::opLAnd, ParseType::mul_exp_mul}, {RuleType::opLOr, ParseType::mul_exp_mul}, {RuleType::opLe, ParseType::mul_exp_mul}, {RuleType::opLt, ParseType::mul_exp_mul}, {RuleType::opMinus, ParseType::mul_exp_mul}, {RuleType::opMod, ParseType::mul_exp_mul}, {RuleType::opMul, ParseType::mul_exp_mul}, {RuleType::opNeq, ParseType::mul_exp_mul}, {RuleType::sepColon, ParseType::mul_exp_mul}, {RuleType::sepRParen, ParseType::mul_exp_mul}, {RuleType::sepRSBrkt, ParseType::mul_exp_mul}, {RuleType::sepSemicolon, ParseType::mul_exp_mul}, }},
	{77, {{RuleType::sepSemicolon, ParseType::stmt_assign}, }},
	{80, {{RuleType::_end, ParseType::block_item_return}, {RuleType::idName, ParseType::block_item_return}, {RuleType::keyBreak, ParseType::block_item_return}, {RuleType::keyContinue, ParseType::block_item_return}, {RuleType::keyFloat, ParseType::block_item_return}, {RuleType::keyIf, ParseType::block_item_return}, {RuleType::keyInt, ParseType::block_item_return}, {RuleType::keyReturn, ParseType::block_item_return}, {RuleType::keyWhile, ParseType::block_item_return}, {RuleType::literalInt, ParseType::block_item_return}, {RuleType::opAdd, ParseType::block_item_return}, {RuleType::opBang, ParseType::block_item_return}, {RuleType::opMinus, ParseType::block_item_return}, {RuleType::sepLCBrkt, ParseType::block_item_return}, {RuleType::sepLParen, ParseType::block_item_return}, {RuleType::sepRCBrkt, ParseType::block_item_return}, }},
	{82, {{RuleType::_end, ParseType::block_item_block}, {RuleType::idName, ParseType::block_item_block}, {RuleType::keyBreak, ParseType::block_item_block}, {RuleType::keyContinue, ParseType::block_item_block}, {RuleType::keyFloat, ParseType::block_item_block}, {RuleType::keyIf, ParseType::block_item_block}, {RuleType::keyInt, ParseType::block_item_block}, {RuleType::keyReturn, ParseType::block_item_block}, {RuleType::keyWhile, ParseType::block_item_block}, {RuleType::literalInt, ParseType::block_item_block}, {RuleType::opAdd, ParseType::block_item_block}, {RuleType::opBang, ParseType::block_item_block}, {RuleType::opMinus, ParseType::block_item_block}, {RuleType::sepLCBrkt, ParseType::block_item_block}, {RuleType::sepLParen, ParseType::block_item_block}, {RuleType::sepRCBrkt, ParseType::block_item_block}, }},
	{83, {{RuleType::opAdd, ParseType::primary_exp_paren_exp}, {RuleType::opDiv, ParseType::primary_exp_paren_exp}, {RuleType::opEq, ParseType::primary_exp_paren_exp}, {RuleType::opGe, ParseType::primary_exp_paren_exp}, {RuleType::opGt, ParseType::primary_exp_paren_exp}, {RuleType::opLAnd, ParseType::primary_exp_paren_exp}, {RuleType::opLOr, ParseType::primary_exp_paren_exp}, {RuleType::opLe, ParseType::primary_exp_paren_exp}, {RuleType::opLt, ParseType::primary_exp_paren_exp}, {RuleType::opMinus, ParseType::primary_exp_paren_exp}, {RuleType::opMod, ParseType::primary_exp_paren_exp}, {RuleType::opMul, ParseType::primary_exp_paren_exp}, {RuleType::opNeq, ParseType::primary_exp_paren_exp}, {RuleType::sepColon, ParseType::primary_exp_paren_exp}, {RuleType::sepRParen, ParseType::primary_exp_paren_exp}, {RuleType::sepRSBrkt, ParseType::primary_exp_paren_exp}, {RuleType::sepSemicolon, ParseType::primary_exp_paren_exp}, }},
	{84, {{RuleType::idName, ParseType::var_type_array}, }},
	{85, {{RuleType::opAdd, ParseType::l_val_indexed_var}, {RuleType::opAssign, ParseType::l_val_indexed_var}, {RuleType::opDiv, ParseType::l_val_indexed_var}, {RuleType::opEq, ParseType::l_val_indexed_var}, {RuleType::opGe, ParseType::l_val_indexed_var}, {RuleType::opGt, ParseType::l_val_indexed_var}, {RuleType::opLAnd, ParseType::l_val_indexed_var}, {RuleType::opLOr, ParseType::l_val_indexed_var}, {RuleType::opLe, ParseType::l_val_indexed_var}, {RuleType::opLt, ParseType::l_val_indexed_var}, {RuleType::opMinus, ParseType::l_val_indexed_var}, {RuleType::opMod, ParseType::l_val_indexed_var}, {RuleType::opMul, ParseType::l_val_indexed_var}, {RuleType::opNeq, ParseType::l_val_indexed_var}, {RuleType::sepColon, ParseType::l_val_indexed_var}, {RuleType::sepRParen, ParseType::l_val_indexed_var}, {RuleType::sepRSBrkt, ParseType::l_val_indexed_var}, {RuleType::sepSemicolon, ParseType::l_val_indexed_var}, }},
	{86, {{RuleType::_end, ParseType::block_item_if}, {RuleType::idName, ParseType::block_item_if}, {RuleType::keyBreak, ParseType::block_item_if}, {RuleType::keyContinue, ParseType::block_item_if}, {RuleType::keyFloat, ParseType::block_item_if}, {RuleType::keyIf, ParseType::block_item_if}, {RuleType::keyInt, ParseType::block_item_if}, {RuleType::keyReturn, ParseType::block_item_if}, {RuleType::keyWhile, ParseType::block_item_if}, {RuleType::literalInt, ParseType::block_item_if}, {RuleType::opAdd, ParseType::block_item_if}, {RuleType::opBang, ParseType::block_item_if}, {RuleType::opMinus, ParseType::block_item_if}, {RuleType::sepLCBrkt, ParseType::block_item_if}, {RuleType::sepLParen, ParseType::block_item_if}, {RuleType::sepRCBrkt, ParseType::block_item_if}, }},
	{87, {{RuleType::_end, ParseType::block_item_while}, {RuleType::idName, ParseType::block_item_while}, {RuleType::keyBreak, ParseType::block_item_while}, {RuleType::keyContinue, ParseType::block_item_while}, {RuleType::keyFloat, ParseType::block_item_while}, {RuleType::keyIf, ParseType::block_item_while}, {RuleType::keyInt, ParseType::block_item_while}, {RuleType::keyReturn, ParseType::block_item_while}, {RuleType::keyWhile, ParseType::block_item_while}, {RuleType::literalInt, ParseType::block_item_while}, {RuleType::opAdd, ParseType::block_item_while}, {RuleType::opBang, ParseType::block_item_while}, {RuleType::opMinus, ParseType::block_item_while}, {RuleType::sepLCBrkt, ParseType::block_item_while}, {RuleType::sepLParen, ParseType::block_item_while}, {RuleType::sepRCBrkt, ParseType::block_item_while}, }},
};
static std::map<ParseType, std::pair<RuleType, std::vector<RuleType>>> parseTypeToRule = {
	{ParseType::add_exp_add, {RuleType::AddExp, {RuleType::AddExp, RuleType::opAdd, RuleType::MulExp, }}},
	{ParseType::add_exp_flow, {RuleType::AddExp, {RuleType::MulExp, }}},
	{ParseType::add_exp_sub, {RuleType::AddExp, {RuleType::AddExp, RuleType::opMinus, RuleType::MulExp, }}},
	{ParseType::basic_type_float, {RuleType::BasicType, {RuleType::keyFloat, }}},
	{ParseType::basic_type_int, {RuleType::BasicType, {RuleType::keyInt, }}},
	{ParseType::block_content_body, {RuleType::BlockContent, {RuleType::BlockItem, RuleType::BlockContent, }}},
	{ParseType::block_content_last, {RuleType::BlockContent, {RuleType::BlockItem, }}},
	{ParseType::block_item_block, {RuleType::BlockItem, {RuleType::sepLCBrkt, RuleType::BlockContent, RuleType::sepRCBrkt, }}},
	{ParseType::block_item_break, {RuleType::BlockItem, {RuleType::keyBreak, RuleType::sepSemicolon, }}},
	{ParseType::block_item_continue, {RuleType::BlockItem, {RuleType::keyContinue, RuleType::sepSemicolon, }}},
	{ParseType::block_item_decl, {RuleType::BlockItem, {RuleType::Decl, RuleType::sepSemicolon, }}},
	{ParseType::block_item_if, {RuleType::BlockItem, {RuleType::keyIf, RuleType::Exp, RuleType::sepColon, RuleType::BlockItem, }}},
	{ParseType::block_item_return, {RuleType::BlockItem, {RuleType::keyReturn, RuleType::Exp, RuleType::sepSemicolon, }}},
	{ParseType::block_item_stmt, {RuleType::BlockItem, {RuleType::Stmt, RuleType::sepSemicolon, }}},
	{ParseType::block_item_while, {RuleType::BlockItem, {RuleType::keyWhile, RuleType::Exp, RuleType::sepColon, RuleType::BlockItem, }}},
	{ParseType::comp_unit, {RuleType::CompUnit, {RuleType::BlockContent, }}},
	{ParseType::const_exp, {RuleType::ConstExp, {RuleType::AddExp, }}},
	{ParseType::decl, {RuleType::Decl, {RuleType::VarType, RuleType::idName, }}},
	{ParseType::exp, {RuleType::Exp, {RuleType::LOrExp, }}},
	{ParseType::l_and_exp_flow, {RuleType::LAndExp, {RuleType::LEqExp, }}},
	{ParseType::l_and_exp_main, {RuleType::LAndExp, {RuleType::LAndExp, RuleType::opLAnd, RuleType::LEqExp, }}},
	{ParseType::l_eq_exp_eq, {RuleType::LEqExp, {RuleType::LEqExp, RuleType::opEq, RuleType::LRelExp, }}},
	{ParseType::l_eq_exp_flow, {RuleType::LEqExp, {RuleType::LRelExp, }}},
	{ParseType::l_eq_exp_neq, {RuleType::LEqExp, {RuleType::LEqExp, RuleType::opNeq, RuleType::LRelExp, }}},
	{ParseType::l_or_exp_flow, {RuleType::LOrExp, {RuleType::LAndExp, }}},
	{ParseType::l_or_exp_main, {RuleType::LOrExp, {RuleType::LOrExp, RuleType::opLOr, RuleType::LAndExp, }}},
	{ParseType::l_rel_exp_flow, {RuleType::LRelExp, {RuleType::AddExp, }}},
	{ParseType::l_rel_exp_ge, {RuleType::LRelExp, {RuleType::LRelExp, RuleType::opGe, RuleType::AddExp, }}},
	{ParseType::l_rel_exp_gt, {RuleType::LRelExp, {RuleType::LRelExp, RuleType::opGt, RuleType::AddExp, }}},
	{ParseType::l_rel_exp_le, {RuleType::LRelExp, {RuleType::LRelExp, RuleType::opLe, RuleType::AddExp, }}},
	{ParseType::l_rel_exp_lt, {RuleType::LRelExp, {RuleType::LRelExp, RuleType::opLt, RuleType::AddExp, }}},
	{ParseType::mul_exp_div, {RuleType::MulExp, {RuleType::MulExp, RuleType::opDiv, RuleType::UnaryExp, }}},
	{ParseType::mul_exp_flow, {RuleType::MulExp, {RuleType::UnaryExp, }}},
	{ParseType::mul_exp_mod, {RuleType::MulExp, {RuleType::MulExp, RuleType::opMod, RuleType::UnaryExp, }}},
	{ParseType::mul_exp_mul, {RuleType::MulExp, {RuleType::MulExp, RuleType::opMul, RuleType::UnaryExp, }}},
	{ParseType::primary_exp_literal_int, {RuleType::PrimaryExp, {RuleType::literalInt, }}},
	{ParseType::primary_exp_paren_exp, {RuleType::PrimaryExp, {RuleType::sepLParen, RuleType::Exp, RuleType::sepRParen, }}},
	{ParseType::primary_exp_r_val, {RuleType::PrimaryExp, {RuleType::Val, }}},
	{ParseType::stmt_assign, {RuleType::Stmt, {RuleType::Val, RuleType::opAssign, RuleType::Exp, }}},
	{ParseType::stmt_exp, {RuleType::Stmt, {RuleType::Exp, }}},
	{ParseType::unary_exp_flow, {RuleType::UnaryExp, {RuleType::PrimaryExp, }}},
	{ParseType::unary_exp_neg, {RuleType::UnaryExp, {RuleType::opMinus, RuleType::UnaryExp, }}},
	{ParseType::unary_exp_not, {RuleType::UnaryExp, {RuleType::opBang, RuleType::UnaryExp, }}},
	{ParseType::unary_exp_pos, {RuleType::UnaryExp, {RuleType::opAdd, RuleType::UnaryExp, }}},
	{ParseType::l_val_indexed_var, {RuleType::Val, {RuleType::idName, RuleType::sepLSBrkt, RuleType::Exp, RuleType::sepRSBrkt, }}},
	{ParseType::l_val_var, {RuleType::Val, {RuleType::idName, }}},
	{ParseType::var_type_array, {RuleType::VarType, {RuleType::BasicType, RuleType::sepLSBrkt, RuleType::ConstExp, RuleType::sepRSBrkt, }}},
	{ParseType::var_type_basic, {RuleType::VarType, {RuleType::BasicType, }}},
};

static NodeID_t start = 0;
static NodeID_t end = 3;

static RuleType startRule = RuleType::CompUnit;
static RuleType endRule = RuleType::_end;

static ParseType theFirstParseType = ParseType::comp_unit;

}
