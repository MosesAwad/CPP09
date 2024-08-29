
#include "PmergeME.hpp"

template <typename T>
void	get_entries(T& entries, char* argv[])
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
			entries.push_back(value);
		else
			throw(InvalidEntry());
		i++;
	}
}

/*
	DONT FORGET TO HANDLE ODD
*/
// std::vector<int>	merge_section(std::vector<int>& vector)
// {
// 	if (vector.size() <= 1)
// 		return vector;
// 	std::vector< std::pair<int,int> > pairs;

// 	size_t	i = 0;
// 	for ( ; i + 1 < vector.size(); i += 2) {
// 		if (vector[i] < vector[i + 1])
// 			pairs.push_back(std::make_pair(vector[i], vector[i + 1]));
// 		else
// 			pairs.push_back(std::make_pair(vector[i + 1], vector[i]));
// 	}

// 	// handle odd number of elements
// 	int extraneous = 0;
// 	if (i < vector.size())
// 		extraneous = vector[i];

// 	// for (size_t i = 0; i < pairs.size(); i++) {
// 	// 	std::cout << "(" << pairs[i].first << "," << pairs[i].second << ")" << " ";
// 	// }
// 	// std::cout << std::endl;

// 	std::vector<int> larger_elements;
// 	for (size_t i = 0; i < pairs.size(); i++) {
// 		larger_elements.push_back(pairs[i].second);
// 	}
// 	larger_elements = merge_section(larger_elements);

// 	std::vector<int> smaller_elements;
// 	for (size_t i = 0; i < pairs.size(); i++) {
// 		smaller_elements.push_back(pairs[i].first);
// 	}

// 	// handle odd number of elements
// 	if (extraneous != 0) 
// 		smaller_elements.push_back(extraneous);
	
// 	for (size_t i = 0; i < smaller_elements.size(); i++) {
// 		std::vector<int>::iterator position = std::lower_bound(larger_elements.begin(), larger_elements.end(), smaller_elements[i]);
// 		larger_elements.insert(position, smaller_elements[i]);
// 	}
// 	return larger_elements;
// }

/*
	DONT FORGET TO HANDLE ODD
*/
template <typename Container>
Container merge_section(Container& container)
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

	T	extraneous = 0;
	if (it != container.end())
		extraneous = *it; 

    Container larger_elements;
    for (size_t i = 0; i < pairs.size(); ++i) {
        larger_elements.push_back(pairs[i].second);
    }
    larger_elements = merge_section(larger_elements);

    Container smaller_elements;
    for (size_t i = 0; i < pairs.size(); ++i) {
        smaller_elements.push_back(pairs[i].first);
    }

	if (extraneous != 0)
		smaller_elements.push_back(extraneous);

    typename Container::iterator ins_it;
    for (it = smaller_elements.begin(); it != smaller_elements.end(); ++it) {
        ins_it = std::lower_bound(larger_elements.begin(), larger_elements.end(), *it);
        larger_elements.insert(ins_it, *it);
    }

    return larger_elements;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		return (std::cerr << "Error: not enough arguments" << std::endl, 1);

	std::cout << "===== MAIN 1 =====" << std::endl;
	{
		std::vector<int> result;
		try {
			get_entries(result, argv);
		}
		catch (std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
			return (1);
		}

		for (size_t i = 0; i < result.size(); i++) {
			std::cout << result[i] << " ";
		}
		std::cout << std::endl;

		std::vector<int> sorted = merge_section(result);
		for (size_t i = 0; i < sorted.size(); i++) {
			std::cout << sorted[i] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "===== MAIN 2 =====" << std::endl;
	{
		std::list<int> result;
		try {
			get_entries(result, argv);
		}
		catch (std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
			return (1);
		}

		for (std::list<int>::iterator it = result.begin(); it != result.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		
		std::list<int> sorted = merge_section(result);
		for (std::list<int>::iterator it = sorted.begin(); it != sorted.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}

	return (0);
}
