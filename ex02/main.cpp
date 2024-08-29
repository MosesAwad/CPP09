
#include "PmergeME.hpp"

size_t	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e6) + (tv.tv_usec));
}

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

template <typename Container>
Container merge_insert_sort(Container& container)
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
	SAVED AS A REFERENCE
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

		// for (size_t i = 0; i < result.size(); i++) {
		// 	std::cout << result[i] << " ";
		// }
		// std::cout << std::endl;

		size_t	start_time = get_time();
		std::vector<int> sorted = merge_insert_sort(result);
		size_t	end_time = get_time();

		// for (size_t i = 0; i < sorted.size(); i++) {
		// 	std::cout << sorted[i] << " ";
		// }
		std::cout << "Time taken is " << end_time - start_time << " us" << std::endl;
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

		// for (std::list<int>::iterator it = result.begin(); it != result.end(); ++it) {
		// 	std::cout << *it << " ";
		// }
		std::cout << std::endl;

		size_t	start_time = get_time();		
		std::list<int> sorted = merge_insert_sort(result);
		size_t	end_time = get_time();

		// for (std::list<int>::iterator it = sorted.begin(); it != sorted.end(); ++it) {
		// 	std::cout << *it << " ";
		// }
		std::cout << "Time taken is " << end_time - start_time << " us" << std::endl;
		std::cout << std::endl;
	}

	return (0);
}

/*
	For a larger number of elements (like 3000), std::vector is
	signifcantly faster. The reason is due to Cache Locaility and 
	Iteration speed far outweighing Insertion Overhead in importance. 
	But, for a smaller number of elements (like < 10), std::list is 
	consistently faster yet negligibly because of its quick insertion 
	speed since memory blocks don't need to be reassigned like an 
	std::vector when they are resized via pushback for instance.

			 			-- Cache Locality --

	1.	std::vector: Elements in a std::vector are stored in 
		contiguous memory, which means that accessing the elements 
		sequentially benefits from CPU cache locality. The CPU can 
		prefetch the next elements efficiently, leading to much 
		faster access times.
	
	2.	std::list: Elements in a std::list are not stored contiguously;
		each element is a separate node in memory connected by pointers. 
		Accessing elements sequentially in a std::list requires following 
		pointers, which results in many cache misses and slower access times.

		So basically, Elements in a std::vector are stored right next to 
		each other in memory. This proximity allows the CPU to load 
		multiple elements into the cache in one go, which makes iterating 
		through the vector very fast. In a std::list, each node is allocated 
		separately in memory. The memory address of the next node could be 
		far away from the current node. When the CPU follows the pointer 
		to the next node, it often needs to load a completely different 
		section of memory into the cache. This process can result in 
		cache misses, where the CPU has to go back to the main memory 
		to fetch the data. Generally speaking, a cache miss is when the 
		data the CPU needs is not in the cache, meaning the CPU has to 
		go to the slower main memory (RAM) to fetch it. This results in 
		a delay because accessing data from RAM is much slower than 
		accessing it from the cache.

						-- Iteration Speed --

	1.	std::vector: Iteration over a std::vector is very fast because the 
		elements are stored in a continuous block of memory. The CPU can 
		read them one after another with minimal overhead.

	2.	std::list: Iterating through a std::list involves dereferencing pointers 
		for each element, which is slower, especially with a large number of 
		elements.

						-- Insertion Overhead --

	1.	std::vector: Insertion can be slower than in a std::list due 
		to the need to shift elements. However, when dealing with 
		larger data sets, the benefits of contiguous storage often 
		outweigh this cost, especially if the operations are mostly 
		reads or involve sorting.
	
	2.	std::list: While std::list offers constant-time insertion and 
		deletion, this advantage diminishes when the cost of non-contiguous 
		memory access is considered, especially as the number of elements 
		increases.
*/