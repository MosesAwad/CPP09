
#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <exception>

class InvalidEntry : public std::exception
{
	const char*	what() const throw();
};

#endif