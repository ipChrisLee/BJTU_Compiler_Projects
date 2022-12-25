#include "Addr.hpp"

namespace liair {

u32 addrCount;

std::map<const Addr *, u32> addr2id;

u32 get_addr_id(const Addr & addr) {
	const auto * pAddr = &addr;
	if (!addr2id.count(&addr)) {
		addr2id[pAddr] = ++addrCount;
	}
	return addr2id[pAddr];
}

std::string addrTypeToString(AddrType addrType) {
	switch (addrType) {
		case AddrType::none_t:
			return "none_t";
		case AddrType::int32_t:
			return "int32_t";
		case AddrType::float_t:
			return "float_t";
		case AddrType::label_t:
			return "label_t";
	}
}

u32 get_addr_id(const Addr * pAddr) {
	if (!addr2id.count(pAddr)) {
		addr2id[pAddr] = ++addrCount;
	}
	return addr2id[pAddr];
}

std::string addr2name(const Addr * pAddr) {
	auto res = std::string();
	res += pAddr->name + "." + addrTypeToString(pAddr->type) + "." +
		std::to_string(get_addr_id(pAddr));
	return res;
}

}