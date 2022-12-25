#pragma once


#include <list>

#include "Addr.hpp"


#include <moe/stl_pro.hpp>

namespace liair {

enum class InstrType {
	none_t,
	label_dec_t,                                //	declare label @dst
	br_t,                                        //	unconditional branch to @dst
	add_t,                                        //	dst = srcL + srcR
};


bool is_br_type(InstrType instrType);

struct Instr {
	InstrType type = InstrType::none_t;
	std::shared_ptr<Addr> srcL = std::shared_ptr<Addr>();
	std::shared_ptr<Addr> srcR = std::shared_ptr<Addr>();
	std::shared_ptr<Addr> dst = std::shared_ptr<Addr>();
	std::list<std::shared_ptr<Addr>> addrLst = std::list<std::shared_ptr<Addr>>();
	std::string to_llvm_ir(std::function<std::string(const Addr *)> addr2name);
};

}