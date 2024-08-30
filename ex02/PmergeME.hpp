
#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <exception>
#include <list>
#include <sys/time.h>

class PmergeMe
{
	private:
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		std::vector<int>	vector;
		std::list<int>		list;
		template <typename Container> Container merge_insert_sort(Container& container);
	public:
		class InvalidEntry;
		PmergeMe();
		~PmergeMe();
		void	get_entries(char* argv[]);
		void	sort_and_display();
};

class PmergeMe::InvalidEntry : public std::exception
{
	public:
		const char*	what() const throw();
};

#endif