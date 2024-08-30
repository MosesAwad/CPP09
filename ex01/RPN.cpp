
#include "RPN.hpp"

/*
	===================================================================
						   ORTHODOX CANONICAL FORM
	===================================================================
*/
RPN::RPN() {}

RPN::RPN(const RPN& other)
{
	*this = other;
}


RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		this->stack = other.stack;
		this->error_token = other.error_token;
	}
	return (*this);
}

RPN::~RPN() {}

/*
	===================================================================
						  		 GETTERS
	===================================================================
*/
std::string&	RPN::getErrorToken()
{
	if (error_token.empty())
		std::cout << "No errors present" << std::endl;
	return (error_token);
}

/*
	===================================================================
								EXCEPTIONS
	===================================================================
*/
const char*	RPN::InvalidEntryOption::what() const throw()
{
	return ("Invalid entry option -> ");
}

const char*	RPN::InvalidRPNOperation::what() const throw()
{
	return ("Invalid RPN operation");
}

/*
	===================================================================
								PARSE INPUT
	===================================================================
*/
static bool	is_op(std::string& str)
{
	std::string operations = "+-/*";

	if (str.size() > 1 || operations.find(str) == std::string::npos)
		return false;
	return true;
}

static bool is_integer(const std::string& str) {
    std::stringstream	ss(str);
    int					value;
    char				remaining;

    if (ss >> value && !(ss >> remaining)) {
        return true;
	}
    return false;
}

/*
	===================================================================
							RPN CALCULATE
	===================================================================
*/
void	RPN::calculate(char *argv[])
{

	std::string 			token_list = argv[1];
	std::istringstream 		stream(token_list);
	std::string				token;

	while (stream >> token) {
		// std::cout << "token : " << token << "." << std::endl;
		if (!is_integer(token) && !is_op(token)) {
			error_token = token;
			throw (InvalidEntryOption());
		}
		if (is_integer(token))
			stack.push(atoi(token.c_str()));
		if (is_op(token))
		{
			int result;
			int store;

			if (stack.size() < 2)
				throw(InvalidRPNOperation());
			store = stack.top();
			stack.pop();
			if (token == "*")
				result = stack.top() * store;
			else if (token == "/")
				result = stack.top() / store;
			else if (token == "+")
				result = stack.top() + store;
			else if (token == "-")
				result = stack.top() - store;
			stack.pop();
			stack.push(result);
		}
	}
	if (stack.size() > 1)
		throw(InvalidRPNOperation());

	std::cout << stack.top() << std::endl;
}
