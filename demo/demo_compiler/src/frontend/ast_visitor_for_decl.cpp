#include "ast_visitor.hpp"

namespace b_lan {


VisitRetPack visit_block_item_decl(const SPtrASTNode & pNode) {
	//  BlockItem       ->	Decl sepSemicolon						%	block_item_decl
	moe_assert(check_sons(pNode, {RuleType::Decl, RuleType::sepSemicolon}));
	return visit_dispatch(pNode->sons[0]);
}

VisitRetPack visit_decl(const SPtrASTNode & pNode) {
	//  Decl			->	VarType IdNames							%	decl
	moe_assert(check_sons(pNode, {RuleType::VarType, RuleType::IdNames}));
	auto addrType = visit_dispatch(pNode->sons[0]).addrType;
	auto names = visit_dispatch(pNode->sons[1]).names;
	for (auto & name: names) {
		auto pAddr = std::make_shared<liair::Addr>(
			liair::Addr{.type=addrType, .name=name}
		);
		symbolTable.push_addr(name, pAddr);
	}
	return { };
}

VisitRetPack visit_var_type_basic(const SPtrASTNode & pNode) {
	//  VarType			->	BasicType								%	var_type_basic
	moe_assert(check_sons(pNode, {RuleType::BasicType}));
	return visit_dispatch(pNode->sons[0]);
}

VisitRetPack visit_basic_type_int(const SPtrASTNode & pNode) {
	//  BasicType		->	keyInt									%	basic_type_int
	moe_assert(check_sons(pNode, {RuleType::keyInt}));
	return VisitRetPack{.addrType=liair::AddrType::int32_t};
}

VisitRetPack visit_id_names_body(const SPtrASTNode & pNode) {
	//  IdNames			->	idName sepComma IdNames					%	id_names_body
	moe_assert(check_sons(pNode, {RuleType::idName, RuleType::sepComma, RuleType::IdNames}));
	auto idNames = visit_dispatch(pNode->sons[2]).names;
	idNames.emplace(idNames.begin(), pNode->sons[0]->content);
	return {.names=idNames};
}

VisitRetPack visit_id_names_last(const SPtrASTNode & pNode) {
	//  IdNames			->	idName              					%	id_names_last
	moe_assert(check_sons(pNode, {RuleType::idName}));
	auto name = pNode->sons[0]->content;
	return {.names={name}};
}

}