
#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: Must use strictly two arguments" << std::endl;
		return (1);
	}
	BitcoinExchange BitcoinExchange;
	BitcoinExchange.file_handling("data.csv");
	BitcoinExchange.extract_rates_database();
	BitcoinExchange.file_handling(argv[1]);
	BitcoinExchange.extract_values_database();
	return (0);
}
