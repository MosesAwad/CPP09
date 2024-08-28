
#include "PmergeME.hpp"

bool	is_integer(char *str)
{
	std::string			string = str;
	std::stringstream	stream(string);
	int					value;
	char				remaining;

	if (stream >> value && !(stream >> remaining))
		return true;
	return false;
}

/*
	CHANGE TO TEMPLATE FUNCTION LATER CUZ IT WILL BE USED
	WITH TWO DIFFERENT CONTAINERS
*/
void	get_entries(std::vector<int>& entries, char *argv[])
{
	int	i;

	i = 1;	// skip the name of the program
	while (argv[i]) {
		if (is_integer(argv[i]) == false)
			throw(InvalidEntry());
		entries.push_back(atoi(argv[i++]));
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Error: not enough arguments" << std::endl;
		return (1);
	}

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
