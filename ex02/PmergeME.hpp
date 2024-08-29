
#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <exception>
#include <list>
#include <sys/time.h>

class InvalidEntry : public std::exception
{
	const char*	what() const throw();
};

#endif