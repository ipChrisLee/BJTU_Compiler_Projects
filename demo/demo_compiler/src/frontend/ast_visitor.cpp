#include "ast_visitor.hpp"

namespace b_lan {
bool check_sons(const SPtrASTNode & pNode, const std::vector<RuleType> & sonTypes) {
	if (pNode->sons.size() != sonTypes.size()) {
		return false;
	}
	for (u32 i = 0; i < pNode->sons.size(); ++i) {
		if (pNode->sons[i]->ruleType != sonTypes[i]) {
			return false;
		}
	}
	return true;
}

VisitRetPack visit_dispatch(const SPtrASTNode & pNode) {
	std::cout << vis_ast_node(pNode) << std::endl;
	if (pNode->parseType.has_value()) {
		switch (pNode->parseType.value()) {
			case ParseType::comp_unit:
				return visit_comp_unit(pNode);
			case ParseType::block_content_body:
				return visit_block_content_body(pNode);
			case ParseType::block_content_last:
				return visit_block_content_last(pNode);
			case ParseType::block_item_decl:
				return visit_block_item_decl(pNode);
			case ParseType::decl:
				return visit_decl(pNode);
			case ParseType::var_type_basic:
				return visit_var_type_basic(pNode);
			case ParseType::basic_type_int:
				return visit_basic_type_int(pNode);
			case ParseType::id_names_body:
				return visit_id_names_body(pNode);
			case ParseType::id_names_last:
				return visit_id_names_last(pNode);
			default:
				return visit_err(pNode);
		}
	} else {
		switch (pNode->ruleType) {
			default:
				return visit_err(pNode);
		}
	}
}

VisitRetPack visit_err(const SPtrASTNode & pNode, std::string_view msg) {
	moe_dbg(vis_ast_node(pNode));
	moe_panic("err visit with msg [" << msg << "]");
}

std::string vis_ast_node(const SPtrASTNode & pNode) {
	auto res = std::string();
	res += "{ content=\"" + pNode->content + "\", ";
	{
		res += "parseType=";
		if (pNode->parseType.has_value()) {
			res += b_lan::parseTypeToStr(pNode->parseType.value());
		} else {
			res += "None";
		}
		res += ", ";
	}
	{
		res += "ruleType=";
		res += b_lan::ruleTypeToStr(pNode->ruleType);
	}
	res += " }";
	return res;
}

void merge_to(
	std::set<std::shared_ptr<liair::Instr>> & to,
	std::vector<std::set<std::shared_ptr<liair::Instr>>> && from
) {
	for (auto & f: from) {
		to.merge(std::move(f));
	}
}

void SymbolTable::push_addr(std::string_view name, std::shared_ptr<liair::Addr> pAddr) {
	moe_assert(!layers.rbegin()->data.count(std::string(name)));
	layers.rbegin()->data.emplace(name, pAddr);
}

std::shared_ptr<liair::Addr> SymbolTable::get_addr(std::string_view name) {
	for (auto itLayer = layers.rbegin(); itLayer != layers.rend(); ++itLayer) {
		auto & layer = *itLayer;
		if (layer.data.count(std::string(name))) {
			return layer.data[std::string(name)];
		}
	}
	moe_panic("");
}

SymbolTable symbolTable;

}