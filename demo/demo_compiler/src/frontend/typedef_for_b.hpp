#pragma once


#include "b_parser_info.hpp"
#include <locgl_runtime.hpp>

namespace b_lan {
using RuleType = b_parser_info::RuleType;
using ParseType = b_parser_info::ParseType;
std::string ruleTypeToStr(RuleType ruleType);
std::string parseTypeToStr(ParseType parseType);
using ASTNode = gast::ASTNodeWithInfo<RuleType, ParseType>;
using SPtrASTNode = std::shared_ptr<ASTNode>;
}
