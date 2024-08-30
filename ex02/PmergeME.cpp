
#include "PmergeME.hpp"


/*
	===================================================================
						   ORTHODOX CANONICAL FORM
	===================================================================
*/
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other) {
		this->vector = other.vector;
		this->list = other.list;
	}
	return (*this);
}

/*
	===================================================================
								EXCEPTIONS
	===================================================================
*/
PmergeMe::~PmergeMe() {}

const char*	PmergeMe::InvalidEntry::what() const throw()
{
	return ("Invalid Entry");
}

/*
	===================================================================
								PARSE INPUT
	===================================================================
*/
void	PmergeMe::get_entries(char* argv[])
{
	int				i;
	std::string		string;
	int				value;
	char			remaining;

	i = 1;
	while (argv[i])
	{
		string = argv[i];
		std::stringstream stream(string);
		if (stream >> value && !(stream >> remaining))
		{
			vector.push_back(value);
			list.push_back(value);
		}
		else
			throw(InvalidEntry());
		i++;
	}
}

/*
	===================================================================
						MERGE INSERT SORT ALGORITHM
	===================================================================

	I decided to use the same function (a template function) to 
	do merge insert sort on both the std::vector and the std::list 
	containers. So, if the function looks a bit complicated, you 
	can take a look at the previous and simpler function off of which 
	this function is based on. The previous function is shown at the 
	bottom of this file and it is used to explicitly sort std::vector<int> 
	which makes it look easier to understand and follow along. But both 
	the template function and this previous function work exactly the 
	same way.
*/
template <typename Container>
Container	PmergeMe::merge_insert_sort(Container& container)
{
    if (container.size() <= 1)
        return container;

    typedef typename Container::value_type T;
    typedef std::pair<T, T> Pair;
    std::vector<Pair> pairs;

    typename Container::iterator it = container.begin();
    while (it != container.end()) {
        T first = *it;

		typename Container::iterator next_it = it;
		next_it++;

        if (next_it == container.end())
			break ;
		T second = *next_it;
		++it;
		++it;
		if (first < second)
			pairs.push_back(std::make_pair(first, second));
		else
			pairs.push_back(std::make_pair(second, first));
    }

	// handle odd number of elements
	T	extraneous = 0;
	if (it != container.end())
		extraneous = *it; 

    Container larger_elements;
    for (size_t i = 0; i < pairs.size(); ++i) {
        larger_elements.push_back(pairs[i].second);
    }
    larger_elements = merge_insert_sort(larger_elements);

    Container smaller_elements;
    for (size_t i = 0; i < pairs.size(); ++i) {
        smaller_elements.push_back(pairs[i].first);
    }

	// handle odd number of elements
	if (extraneous != 0)
		smaller_elements.push_back(extraneous);

    typename Container::iterator ins_it;
    for (it = smaller_elements.begin(); it != smaller_elements.end(); ++it) {
        ins_it = std::lower_bound(larger_elements.begin(), larger_elements.end(), *it);
        larger_elements.insert(ins_it, *it);
    }

    return larger_elements;
}

/*
	===================================================================
					SORT AND DISPLAY FUNCTION ALONG
						WITH HELPER FUNCTIONS
	===================================================================
*/
static size_t	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e6) + (tv.tv_usec));
}

template <typename Container>
static void	print_container(Container& container)
{
	typedef typename Container::const_iterator const_iter;

	for (const_iter iter = container.begin(); iter != container.end(); iter++) {
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::sort_and_display()
{
	// STD::VECTOR SECTION
	std::cout << "Before: ";
	print_container(vector);

	size_t	start_v_time = get_time();
	vector = merge_insert_sort(vector);
	size_t	end_v_time = get_time();
	std::cout << "After: ";
	print_container(vector);

	std::cout << "Time taken to process a range of " << vector.size() 
		<< " elements with std::vector : " << end_v_time - start_v_time 
		<< " us" << std::endl;

	// STD::LIST SECTION
	size_t	start_l_time = get_time();
	list = merge_insert_sort(list);
	size_t	end_l_time = get_time();

	std::cout << "Time taken to process a range of " << list.size() 
		<< " elements with std::list : " << end_l_time - start_l_time 
		<< " us" << std::endl;
}

/*
	===================================================================
				OLD PROTOTYPE MERGE INSERT SORT FUNCTION THAT
					WORKS BUT ONLY WITH STD::VECTOR
	===================================================================
*/
/*
	std::vector<int>	merge_insert_sort(std::vector<int>& vector)
	{
		if (vector.size() <= 1)
			return vector;
		std::vector< std::pair<int,int> > pairs;

		size_t	i = 0;
		for ( ; i + 1 < vector.size(); i += 2) {
			if (vector[i] < vector[i + 1])
				pairs.push_back(std::make_pair(vector[i], vector[i + 1]));
			else
				pairs.push_back(std::make_pair(vector[i + 1], vector[i]));
		}

		// handle odd number of elements
		int extraneous = 0;
		if (i < vector.size())
			extraneous = vector[i];

		std::vector<int> larger_elements;
		for (size_t i = 0; i < pairs.size(); i++) {
			larger_elements.push_back(pairs[i].second);
		}
		larger_elements = merge_insert_sort(larger_elements);

		std::vector<int> smaller_elements;
		for (size_t i = 0; i < pairs.size(); i++) {
			smaller_elements.push_back(pairs[i].first);
		}

		// handle odd number of elements
		if (extraneous != 0) 
			smaller_elements.push_back(extraneous);
		
		for (size_t i = 0; i < smaller_elements.size(); i++) {
			std::vector<int>::iterator position = std::lower_bound(larger_elements.begin(), larger_elements.end(), smaller_elements[i]);
			larger_elements.insert(position, smaller_elements[i]);
		}
		return larger_elements;
	}
*/
