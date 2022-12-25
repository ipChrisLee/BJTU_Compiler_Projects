#pragma once


#include <list>
#include <set>

#include <moe/stl_pro.hpp>

#include <liair/Instr.hpp>

#include "typedef_for_b.hpp"

namespace b_lan {

struct VisitRetPack {
	std::list<std::shared_ptr<liair::Instr>>
		instrs = std::list<std::shared_ptr<liair::Instr>>();
	std::set<std::shared_ptr<liair::Instr>>
		linkChainSet = std::set<std::shared_ptr<liair::Instr>>();
	std::set<std::shared_ptr<liair::Instr>>
		linkTCSet = std::set<std::shared_ptr<liair::Instr>>();
	std::set<std::shared_ptr<liair::Instr>>
		linkFCSet = std::set<std::shared_ptr<liair::Instr>>();
	std::set<std::shared_ptr<liair::Instr>>
		linkBrkSet = std::set<std::shared_ptr<liair::Instr>>();
	std::set<std::shared_ptr<liair::Instr>>
		linkContSet = std::set<std::shared_ptr<liair::Instr>>();
	liair::AddrType addrType = liair::AddrType::none_t;
	std::vector<std::string> names = std::vector<std::string>();
};

struct SymbolTable {
	struct SymbolTableLayer {
		std::map<std::string, std::shared_ptr<liair::Addr>> data;
	};
	std::vector<SymbolTableLayer> layers;
	
	void push_layer() { layers.emplace_back(); }
	
	void pop_layer() { layers.pop_back(); }
	
	void push_addr(std::string_view name, std::shared_ptr<liair::Addr> pAddr);
	
	std::shared_ptr<liair::Addr> get_addr(std::string_view name);
};

extern SymbolTable symbolTable;

void merge_to(
	std::set<std::shared_ptr<liair::Instr>> & to,
	std::vector<std::set<std::shared_ptr<liair::Instr>>> && from
);

bool check_sons(const SPtrASTNode & pNode, const std::vector<RuleType> & sonTypes);

VisitRetPack visit_dispatch(const SPtrASTNode & pNode);

VisitRetPack visit_err(const SPtrASTNode & pNode, std::string_view msg = "");

std::string vis_ast_node(const SPtrASTNode & pNode);


//	ast_visitor_for_block.cpp
VisitRetPack visit_comp_unit(const SPtrASTNode & pNode);
VisitRetPack visit_block_content_body(const SPtrASTNode & pNode);
VisitRetPack visit_block_content_last(const SPtrASTNode & pNode);


//	ast_visitor_for_decl.cpp
VisitRetPack visit_block_item_decl(const SPtrASTNode & pNode);
VisitRetPack visit_decl(const SPtrASTNode & pNode);
VisitRetPack visit_var_type_basic(const SPtrASTNode & pNode);
VisitRetPack visit_basic_type_int(const SPtrASTNode & pNode);
VisitRetPack visit_id_names_body(const SPtrASTNode & pNode);
VisitRetPack visit_id_names_last(const SPtrASTNode & pNode);


}