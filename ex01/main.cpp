
#include <stack>
#include <iostream>
#include <sstream>

bool	is_op(std::string& str)
{
	std::string operations = "+-/*";

	if (str.size() > 1 || operations.find(str) == std::string::npos)
		return false;
	return true;
}

bool is_integer(const std::string& str) {
    std::stringstream	ss(str);
    int					value;
    char				remaining;

    if (ss >> value && !(ss >> remaining)) {
        return true;
	}
    return false;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Must use strictly 2 arguments" << std::endl;
		return (1);
	}
	std::string 			token_list = argv[1];
	std::stack<std::string>	stack;
	std::istringstream 		stream(token_list);
	std::string				token;

	while (stream >> token) {
		std::cout << "token : " << token << "." << std::endl;
		if (!is_integer(token) && !is_op(token))
			return (std::cerr << "Invalid entry option -> " << token << std::endl, 1);
	}
	return (0);
}
