#pragma once

#include <vector>
#include <iostream>
#include <cstdint>


namespace lialex_runtime {

using NodeID_t = uint64_t;

template<typename TokenType>
struct Token {
	TokenType tokenType;
	std::string content;
	
	Token(TokenType tokenType, std::string content) :
		tokenType(tokenType), content(std::move(content)) {}
	
	Token(const Token &) = default;
	
	Token(Token &&) noexcept = default;
	
};

template<typename TokenType>
struct Lexer {
	static_assert(std::is_enum<TokenType>::value);
	std::map<NodeID_t, TokenType> nodeType;
	std::map<NodeID_t, std::map<char, NodeID_t>> edges;
	NodeID_t start = -1;
	NodeID_t now = -1;
	std::set<TokenType> tokensToBeThrown;
	
	
	std::vector<Token<TokenType>> gen(std::string str) {
		if (now == -1 || start == -1) {
			std::cerr << "You should specify `start` and `now`!" << std::endl;
			exit(-1);
		}
		auto res = std::vector<Token<TokenType>>();
		auto emplace = [&res, this](TokenType tokenType, std::string buffer) {
			if (!tokensToBeThrown.count(tokenType)) {
				res.template emplace_back(tokenType, std::move(buffer));
			}
		};
		auto buffer = std::string();
		for (auto it = str.begin(); it != str.end(); ++it) {
			auto c = *it;
//			std::cerr << now << std::endl;
//			std::cerr << int(c) << std::endl;
			if (edges.count(now) && edges[now].count(c)) {
				//  Node now has edge with 'c'.
				buffer.push_back(c);
				now = edges[now][c];
			} else {    //  Node `now` has no edge with 'c';
				if (nodeType.count(now)) {
					emplace(nodeType[now], buffer);
					--it;
					buffer.clear();
					now = start;
				} else {
					std::cerr << "Error when trans[" << int(c) << "]!" << std::endl;
					exit(-1);
				}
			}
		}
		if (nodeType.count(now)) {
			emplace(nodeType[now], buffer);
		} else {
			std::cerr << "Error at end!" << std::endl;
			exit(-1);
		}
		return res;
	}
};

}


