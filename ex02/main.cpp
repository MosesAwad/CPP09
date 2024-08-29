
#include "PmergeME.hpp"
#include <exception>

int main(int argc, char *argv[])
{
	if (argc < 2)
		return (std::cerr << "Error: not enough arguments" << std::endl, 1);

	PmergeMe PmergeMe;

	try {
		PmergeMe.get_entries(argv);
	}
	catch (std::exception& e) {
		return (std::cerr << "Error: " << e.what() << std::endl, 1);
	}
	PmergeMe.sort_and_display();

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