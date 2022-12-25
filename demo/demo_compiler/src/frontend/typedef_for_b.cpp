#include "typedef_for_b.hpp"

namespace b_lan {
std::string ruleTypeToStr(RuleType ruleType) {
	return b_parser_info::ruleTypeToStr(ruleType);
}

std::string parseTypeToStr(ParseType parseType) {
	return b_parser_info::parseTypeToStr(parseType);
}
}