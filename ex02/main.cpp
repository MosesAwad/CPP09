
#include "PmergeME.hpp"

/*
	CHANGE TO TEMPLATE FUNCTION LATER CUZ IT WILL BE USED
	WITH TWO DIFFERENT CONTAINERS
*/
void	get_entries(std::vector<int>& entries, char *argv[])
{
	int					i;
	std::string			string;
	int					value;
	char				remaining;

	i = 1;	// skip the name of the program
	while (argv[i]) {
		string = argv[i];
		std::stringstream	stream(string);
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
std::vector<int>	merge_section(std::vector<int>& vector)
{
	if (vector.size() <= 1)
		return vector;
	std::vector< std::pair<int,int> > pairs;
	for (size_t i = 0; i + 1 < vector.size(); i += 2) {
		if (vector[i] < vector[i + 1])
			pairs.push_back(std::make_pair(vector[i], vector[i + 1]));
		else
			pairs.push_back(std::make_pair(vector[i + 1], vector[i]));
	}

	std::vector<int> larger_elements;
	for (size_t i = 0; i < pairs.size(); i++) {
		larger_elements.push_back(pairs[i].second);
	}
	larger_elements = merge_section(larger_elements);

	std::vector<int> smaller_elements;
	for (size_t i = 0; i < pairs.size(); i++) {
		smaller_elements.push_back(pairs[i].first);
	}
	
	for (size_t i = 0; i < smaller_elements.size(); i++) {
		std::vector<int>::iterator position = std::lower_bound(larger_elements.begin(), larger_elements.end(), smaller_elements[i]);
		larger_elements.insert(position, smaller_elements[i]);
	}
	return larger_elements;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		return (std::cerr << "Error: not enough arguments" << std::endl, 1);

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

	return (0);
}
