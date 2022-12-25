#include "ast_visitor.hpp"

namespace b_lan {

VisitRetPack visit_comp_unit(const SPtrASTNode & pNode) {
	moe_assert(check_sons(pNode, {RuleType::BlockContent}));
	symbolTable.push_layer();
	return visit_dispatch(pNode->sons[0]);
}

VisitRetPack visit_block_content_body(const SPtrASTNode & pNode) {
	//	BlockContent	->	BlockItem BlockContent					%	block_content_body
	moe_assert(check_sons(pNode, {RuleType::BlockItem, RuleType::BlockContent}));
	auto packL = visit_dispatch(pNode->sons[0]);
	auto packR = visit_dispatch(pNode->sons[1]);
	{
		auto linksFromLeft = std::set<std::shared_ptr<liair::Instr>>();
		merge_to(linksFromLeft, {packL.linkChainSet, packL.linkTCSet, packL.linkFCSet});
		if (!linksFromLeft.empty()) {
			auto pBeginLabel = std::make_shared<liair::Addr>(
				liair::Addr{.type=liair::AddrType::label_t, .name="export"}
			);
			auto pLabelInstr = std::make_shared<liair::Instr>(
				liair::Instr{.type=liair::InstrType::label_dec_t, .dst=pBeginLabel}
			);
			for (auto & pInstr: linksFromLeft) {
				pInstr->dst = pBeginLabel;
			}
			packR.instrs.insert(packR.instrs.begin(), std::move(pLabelInstr));
		}
	}
	{
		packR.linkBrkSet.merge(std::move(packL.linkBrkSet));
		packR.linkContSet.merge(std::move(packL.linkContSet));
	}
	{
		packR.instrs.insert(packR.instrs.begin(), packL.instrs.begin(), packL.instrs.end());
	}
	return packR;
}

VisitRetPack visit_block_content_last(const SPtrASTNode & pNode) {
	//	BlockContent	->	BlockItem								%	block_content_last
	moe_assert(check_sons(pNode, {RuleType::BlockItem}));
	return visit_dispatch(pNode->sons[0]);
}

}
