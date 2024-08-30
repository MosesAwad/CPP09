
#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <exception>

class RPN
{
	private:
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		std::stack<int>			stack;
		std::string				error_token;
	public:
		class InvalidEntryOption;
		class InvalidRPNOperation;
		RPN();
		~RPN();
		void			calculate(char *argv[]);
		std::string&	getErrorToken();
};

class RPN::InvalidEntryOption : public std::exception
{
	public:
		const char*	what() const throw();
};

class RPN::InvalidRPNOperation : public std::exception
{
	public:
		const char*	what() const throw();
};

#endif