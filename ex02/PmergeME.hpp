
#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <exception>
#include <list>

class InvalidEntry : public std::exception
{
	const char*	what() const throw();
};

#endif