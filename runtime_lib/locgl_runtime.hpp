#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <string_view>
#include <functional>


namespace locgl_runtime {

using NodeID_t = uint64_t;

template<typename TokenType>
struct Token {
	TokenType tokenType;
	std::string content;
	
	Token(
		std::string_view src,
		std::function<TokenType(std::string_view str)> & strToTokenType
	) {
		using namespace std::string_view_literals;
		auto res = std::vector<std::string>();
		auto posStart = std::string_view::size_type(0);
		while (posStart < src.size()) {
			auto iFirstDel = src.size();
			for (auto ch: "\n \t"sv) {
				auto i = src.find(ch, posStart);
				if (i != std::string_view::npos) {
					iFirstDel = std::min(iFirstDel, i);
				}
			}
			if (iFirstDel > posStart) {
				res.emplace_back(src.substr(posStart, iFirstDel - posStart));
			}
			posStart = iFirstDel + 1;
		}
		assert(res.size() > 2);
		tokenType = strToTokenType(res[0]);
		for (auto i = size_t(1); i < res.size(); ++i) {
			assert(res[i].size() == 1);
			content.push_back(res[i][0]);
		}
	}
	
	Token(const Token &) = default;
	
	Token(Token &&) noexcept = default;
	
	static_assert(std::is_enum<TokenType>::value, "Template argument should be enum.");
};

template<typename TokenType>
struct Parser {
	//
	std::map<TokenType, std::vector<TokenType>> first, follow;
	
};
}