#pragma once


#include <string>
#include <map>

#include <moe/moe_typedef.hpp>

namespace liair {

enum class AddrType {
	none_t,
	int32_t,
	float_t,
	label_t,
};


std::string addrTypeToString(AddrType addrType);

struct Addr {
	AddrType type = AddrType::none_t;
	std::string name = std::string("");
	
	[[nodiscard]] std::string to_string() const {
		auto res = std::string();
		res += "{ type=" + addrTypeToString(type) + ", ";
		res += "name=\"" + name + "\"";
		res += " }";
		return res;
	}
};

u32 get_addr_id(const Addr & addr);
u32 get_addr_id(const Addr * pAddr);

std::string addr2name(const Addr * pAddr);

}