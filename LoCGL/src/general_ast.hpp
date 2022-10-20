#pragma once

#include <string>
#include <type_traits>
#include <memory>


namespace gast { //  general ast

template<typename NodeType>
struct ASTNode {
	NodeType nodeType;
	std::string content;
	std::unique_ptr<ASTNode<NodeType>> sons;
	static_assert(std::is_enum<NodeType>::value, "Template argument should be enum.");
	using Node = ASTNode<NodeType>;
};

}