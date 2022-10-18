#include "regex_analyze.hpp"

#include <filesystem>
#include "moe/debugger.hpp"
#include <memory>
#include "moe/log.hpp"


RegexASTNode::RegexASTNode(char ch) : infoType(RegexASTNodeInfoType::ch), info(ch) {
}

RegexASTNode::RegexASTNode(RegexOperator op) :
	infoType(RegexASTNodeInfoType::op), info(op) {
}

std::string RegexASTNode::info_to_string() const {
	switch (infoType) {
		case RegexASTNodeInfoType::ch: {
			auto ch = std::get<char>(info);
			return "\'" + std::to_string(ch) + "\'";
		}
		case RegexASTNodeInfoType::op: {
			auto op = std::get<RegexOperator>(info);
			return regex_operator_to_string(op);
		}
		case RegexASTNodeInfoType::another_rule:
			auto name = std::get<std::string>(info);
			return name;
	}
}

std::unique_ptr<moe::Cloneable> RegexASTNode::clone_to_unique_ptr_to_impl() const {
	return std::make_unique<RegexASTNode>(*this);
}

RegexASTNode::RegexASTNode(std::string anotherRuleName) :
	infoType(RegexASTNodeInfoType::another_rule), info(std::move(anotherRuleName)) {
}

RegexASTNode::RegexASTNode(
	RegexASTNodeInfoType infoType, RegexASTNode::Info_t info
) : infoType(infoType), info(std::move(info)) {
}

RegexASTNode::RegexASTNode(const RegexASTNode & o) :
	RegexASTNode(o.infoType, o.info) {
	for (const auto & upChild: o.children) {
		children.emplace_back(
			moe::dyn_cast_up<RegexASTNode>(upChild->clone_to_unique_ptr()));
	}
}

std::unique_ptr<RegexASTNode> merge_node(
	std::unique_ptr<RegexASTNode> && pLeft, RegexOperator op,
	std::unique_ptr<RegexASTNode> && pRight
) {
	auto newRoot = std::make_unique<RegexASTNode>(op);
	newRoot->children.emplace_back(std::move(pLeft));
	newRoot->children.emplace_back(std::move(pRight));
	return newRoot;
}

std::unique_ptr<RegexASTNode>
merge_node(RegexOperator op, std::unique_ptr<RegexASTNode> && pOperand) {
	auto newRoot = std::make_unique<RegexASTNode>(op);
	newRoot->children.emplace_back(std::move(pOperand));
	return newRoot;
}

static char escape_to_char(char escape) {
	switch (escape) {
		case 'n':
			return '\n';
		case 's':
			return ' ';
		case 't':
			return '\t';
		case '\'':
			return '\'';
		case '\\':
			return '\\';
		case 'r':
			return '\r';
		default:
//			std::cerr << i32(escape) << std::endl;
			moe_panic("Unsupported escape char.");
	}
}

enum class TokenType {
	ch,
	another_rule,
	l_bra,
	r_bra,
	multi,
	or_cond,
	concat,
};
using TokenPair = std::pair<TokenType, std::string>;

static std::unique_ptr<RegexASTNode>
generate(
	std::vector<TokenPair> && pairs,
	const std::map<Rule, std::unique_ptr<RegexASTNode>> & res
) {
	pairs.emplace(pairs.begin(), TokenType::l_bra, "");
	pairs.emplace_back(TokenType::r_bra, "");
	auto stNodes = std::stack<std::unique_ptr<RegexASTNode>>();
	auto stOp = std::stack<TokenType>();
	for (const auto & pair: pairs) {
		switch (pair.first) {
			case TokenType::ch: {
				auto c = pair.second[1];
				if (c == '\\') {
					c = escape_to_char(pair.second[2]);
				}
				auto p = std::make_unique<RegexASTNode>(c);
				stNodes.emplace(std::move(p));
				break;
			}
			case TokenType::another_rule: {
				auto p = std::unique_ptr<RegexASTNode>();
				for (const auto & ruleAndNode: res) {
					if (ruleAndNode.first.name == pair.second) {
						p = std::make_unique<RegexASTNode>(*ruleAndNode.second);
						break;
					}
				}
				moe_assert(p, "Can NOT find spec rule.");
				stNodes.emplace(std::move(p));
				break;
			}
			case TokenType::l_bra: {
				stOp.push(TokenType::l_bra);
				break;
			}
			case TokenType::r_bra: {
				while (stOp.top() != TokenType::l_bra) {
					moe_assert(stNodes.size() >= 2);
					auto pR = std::move(stNodes.top());
					stNodes.pop();
					auto pL = std::move(stNodes.top());
					stNodes.pop();
					auto op = stOp.top();
					stOp.pop();
					switch (op) {
						case TokenType::or_cond:
							stNodes.push(
								merge_node(
									std::move(pL), RegexOperator::or_cond,
									std::move(pR)));
							break;
						case TokenType::concat:
							stNodes.push(
								merge_node(
									std::move(pL), RegexOperator::concat,
									std::move(pR)));
							break;
						default:
							moe_panic("Error");
					}
				}
				stOp.pop(); //  pop '('
				break;
			}
			case TokenType::multi: {
				moe_assert(!stNodes.empty());
				auto pPre = std::move(stNodes.top());
				stNodes.pop();
				stNodes.push(merge_node(RegexOperator::multi, std::move(pPre)));
				break;
			}
			case TokenType::or_cond: {
				while (!stOp.empty() && stOp.top() == TokenType::multi) {
					moe_assert(stNodes.size() >= 2);
					auto pR = std::move(stNodes.top());
					stNodes.pop();
					auto pL = std::move(stNodes.top());
					stNodes.pop();
//					auto op = stOp.top();
					stOp.pop();
					stNodes.push(
						merge_node(
							std::move(pL), RegexOperator::concat,
							std::move(pR)));
				}
				stOp.push(TokenType::or_cond);
				break;
			}
			case TokenType::concat: {
				stOp.push(TokenType::concat);
				break;
			}
		}
	}
	moe_assert(stNodes.size() == 1);
	auto p = std::move(stNodes.top());
	stNodes.pop();
	return p;
}

static std::unique_ptr<RegexASTNode>
from_tokens_to_regex_ast(
	const std::vector<std::string> & tokens,
	const std::map<Rule, std::unique_ptr<RegexASTNode>> & res
) {
	auto pairs = std::vector<TokenPair>();
	for (const auto & token: tokens) {
		if (token[0] == '\'') {
			pairs.emplace_back(TokenType::ch, token);
		} else if (token[0] == '&') {
			pairs.emplace_back(
				TokenType::another_rule, token.substr(1, std::string::npos));
		} else if (token[0] == '(') {
			pairs.emplace_back(TokenType::l_bra, token);
		} else if (token[0] == ')') {
			pairs.emplace_back(TokenType::r_bra, token);
		} else {
			auto tokenType = [&token]() {
				switch (token[0]) {
					case '*':
						return TokenType::multi;
					case '|':
						return TokenType::or_cond;
					case '~':
						return TokenType::concat;
					default:
						moe_panic("Unsupported regex operator.");
				}
			}();
			pairs.emplace_back(tokenType, token);
		}
	}
	return generate(std::move(pairs), res);
}

std::string char_to_dot_string(char c) {
	auto s = std::string();
	s.push_back('"');
	switch (c) {
		case '\n':
			s += "\\\\n";
			break;
		case '\t':
			s += "\\\\t";
			break;
		case ' ':
			s += "\\\\s";
			break;
		case '"':
			s += "\\\"";
			break;
		case '\\':
			s += "back slash";
			break;
		case '\0':
			s += "epsilon";
			break;
		default:
			s.push_back(c);
			break;
	}
	s.push_back('"');
	return s;
}

std::map<Rule, std::unique_ptr<RegexASTNode>>
scan_tex_rules(std::string_view filePath) {
	auto res = std::map<Rule, std::unique_ptr<RegexASTNode>>();
	moe_assert(std::filesystem::exists(filePath), "Lex file does not exist.");
	auto lexStrStream = std::ifstream(filePath);
	auto buf = std::string();
	auto ruleRank = i32(0);
	while (std::getline(lexStrStream, buf)) {
		auto tokens = moe::split_string_on_char(buf, " \n");
		if (tokens.empty()) { continue; }
		auto ruleTypeStr = tokens[0];
		moe_assert(ruleTypeStr.length() == 1);
		auto oRuleType = [&]() -> std::optional<RuleType> {
			switch (ruleTypeStr[0]) {
				case '+':
					return RuleType::Normal;
				case '-':
					return RuleType::Anonymous;
				case '@':
					return RuleType::Throw;
				case '/':
					return { };
				default:
					moe_panic("Unsupported rule!")
			}
		}();
		if (!oRuleType.has_value()) {
			continue;
		}
		moe_assert(
			tokens.size() >= 4,
			"You should have at least four parts of one rule."
		);
		
		auto ruleType = oRuleType.value();
		auto ruleName = tokens[1];
		auto rule = Rule{ruleName, ruleType, ++ruleRank};
		moe_assert(res.count(rule) == 0, "Duplicate name!");
		moe_assert(tokens[2] == "=", "Third part should be \"=\".");
//		from_tokens_to_regex_ast()
		auto upASTNode = from_tokens_to_regex_ast(
			moe::sub_vector(std::move(tokens), 3, -1), res
		);
		moe_assert(upASTNode);
		res.emplace(std::move(rule), std::move(upASTNode));
	}
	for (const auto & ruleAndAST: res) {
		auto dotFilePath = "logs/regex_ast/" + ruleAndAST.first.name + ".dot";
		auto lLog = moe_llog(dotFilePath, " ", true, "//");
		lLog.info("digraph", ruleAndAST.first.name, "{");
		auto cnt = i32(0);
		std::function<int(const std::unique_ptr<RegexASTNode> &)>
			dfs = [&](const std::unique_ptr<RegexASTNode> & u) -> i32 {
			auto idU = ++cnt;
			auto infoStr = [&u]() {
				auto res = std::string();
				switch (u->infoType) {
					case RegexASTNodeInfoType::ch: {
						auto c = std::get<char>(u->info);
						res = char_to_dot_string(c);
						break;
					}
					case RegexASTNodeInfoType::op:
						res = "\"" + regex_operator_to_string(
							std::get<RegexOperator>(u->info)) + "\"";
						break;
					case RegexASTNodeInfoType::another_rule:
						moe_panic("At this time, this should not exist.");
				}
				return res;
			}();
			lLog.info(idU, "[label =", infoStr, "]");
			for (const auto & v: u->children) {
				auto idV = dfs(v);
				lLog.info(idU, "->", idV);
			}
			return idU;
		};
		dfs(ruleAndAST.second);
		lLog.info("}");
	}
	return res;
}

std::string regex_operator_to_string(RegexOperator op) {
	switch (op) {
		case RegexOperator::multi:
			return "*";
		case RegexOperator::or_cond:
			return "|";
		case RegexOperator::concat:
			return "~";
	}
}
