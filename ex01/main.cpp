
#include "RPN.hpp"

int main(int argc, char* argv[])
{
	if (argc != 2)
		return (std::cerr << "Must use strictly 2 arguments" << std::endl, 1);

	RPN	RPN;

	try {
		RPN.calculate(argv);
	}
	catch (RPN::InvalidEntryOption& e) {
		std::cerr << "Error: " << e.what() << RPN.getErrorToken() << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return (0);
}
