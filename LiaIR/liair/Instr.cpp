#include "Instr.hpp"


namespace liair {

bool is_br_type(InstrType instrType) {
	return moe::enum_in(instrType, {InstrType::br_t});
}

std::string Instr::to_llvm_ir(std::function<std::string(const Addr *)> addr2name) {
	auto res = std::string();
	switch (type) {
		case InstrType::label_dec_t: {
			res += addr2name(dst.get()) + ":";
			break;
		}
		case InstrType::none_t:
			moe_panic("Converting a none_t instr to llvm-ir.");
		default:
			moe_rt_todo();
	}
	return res;
}
}
