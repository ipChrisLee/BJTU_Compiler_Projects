#include <iostream>
#include <moe/decorator.hpp>


int main() {
	std::cout << moe::set_decorator(moe::Decorator::c_blue) << "Hello, World!"
	          << std::endl;
	return 0;
}
