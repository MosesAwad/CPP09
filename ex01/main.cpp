
#include "RPN.hpp"

// int main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 		return (std::cerr << "Must use strictly 2 arguments" << std::endl, 1);

// 	std::string 			token_list = argv[1];
// 	std::stack<int>			stack;
// 	std::istringstream 		stream(token_list);
// 	std::string				token;

// 	while (stream >> token) {
// 		std::cout << "token : " << token << "." << std::endl;
// 		if (!is_integer(token) && !is_op(token))
// 			return (std::cerr << "Invalid entry option -> " << token << std::endl, 1);
// 		if (is_integer(token))
// 			stack.push(atoi(token.c_str()));
// 		if (is_op(token))
// 		{
// 			int result;
// 			int store;

// 			store = stack.top();
// 			stack.pop();
// 			if (token == "*")
// 				result = stack.top() * store;
// 			else if (token == "/")
// 				result = stack.top() / store;
// 			else if (token == "+")
// 				result = stack.top() + store;
// 			else if (token == "-")
// 				result = stack.top() - store;
// 			stack.pop();
// 			stack.push(result);
// 		}
// 	}
// 	if (stack.size() > 1)
// 	{
// 		std::cerr << "Invalid RPN operation" << std::endl;
// 		return (2);
// 	}
// 	std::cout << "Result is -> " << stack.top() << std::endl;
// 	return (0);
// }

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
