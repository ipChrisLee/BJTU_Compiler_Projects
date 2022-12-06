#pragma once


#include <set>
#include <string>
#include <moe/moe_typedef.hpp>
#include <moe/debugger.hpp>

#include "grammar_plus.hpp"

namespace slr1 {

struct SLR1Analyzer : gra::GraP { //  SLL(1) analyzer
  protected:
	std::set<std::string> toEpsilon;
	std::map<std::string, std::set<std::string>> first;
	std::map<std::string, std::set<std::string>> follow;
	
	void analyze_epsilon_reachable();
	
	std::set<std::string> first_of(const std::vector<std::string> & items);
	
	void get_first();
	
	void get_follow();
	
	using NodeID_t = u64;
	
	struct NodeContent {
		std::set<std::pair<std::string, std::vector<std::string>>> stmts;
		
		bool operator<(const NodeContent & other) const {
			return stmts < other.stmts;
		}
		
		[[nodiscard]] NodeContent read_operation(const std::string & a) const {
			//  读a生成新的Node
			auto newStmts = std::set<std::pair<std::string, std::vector<std::string>>>();
			for (auto [A, deta]: stmts) {
				auto toAdd = false;
				for (auto it = deta.begin(); it != deta.end(); ++it) {
					if (*it == gra::dot) {
						if (std::next(it) != deta.end() && *std::next(it) == a) {
							std::swap(*it, *std::next(it));
							toAdd = true;
							break;
						}
					}
				}
				if (toAdd) {
					newStmts.emplace(std::move(A), std::move(deta));
				}
			}
			return {newStmts};
		}
		
		[[nodiscard]] NodeContent closure_operation(gra::GraP & graP) const {
			auto newStmts = stmts;
			do {
				auto preSz = newStmts.size();
				for (auto [A, deta]: newStmts) {
					for (auto it = deta.begin(); it != deta.end(); ++it) {
						if (*it == gra::dot && std::next(it) != deta.end() &&
							!graP.isTerm[*std::next(it)]) {
							auto B = *std::next(it);
							//  A -> ... dot B ...
							for (auto [_, right]: graP.allRules[B]) {
								right.emplace(right.begin(), gra::dot);
								newStmts.emplace(B, right);
							}
						}
					}
				}
				if (newStmts.size() == preSz) {
					break;
				}
			} while (true);
			return {newStmts};
		}
		
		void log_it(moe::LocalLog & lLog) const {
			for (const auto & [left, right]: stmts) {
				auto buf = std::string();
				buf += left;
				buf += " ->";
				for (const auto & item: right) {
					buf += " " + item;
				}
				lLog.info(buf);
			}
		}
	};
	
	NodeID_t cnt = 0, start = 0, end = -1;
	std::map<NodeContent, NodeID_t> content2id;
	std::map<NodeID_t, NodeContent> id2content;
	std::map<NodeID_t, std::map<std::string, NodeID_t>> edges;
	
	void get_graph();
  
  public:
	void analyze();
	
	void log_it(moe::LocalLog & lLog) override;
	
	void to_slr1_parser_info(std::string_view filePath, std::string_view parserName);
	
};

}
