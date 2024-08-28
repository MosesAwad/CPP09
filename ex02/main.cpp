
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
		std::cout << result[i] << " " << std::endl;
	}
	return (0);
}
