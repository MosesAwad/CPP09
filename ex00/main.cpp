
#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	BitcoinExchange BitcoinExchange;

	// OLD:	// std::ifstream rates_database("data.csv");
			// if (!rates_database.is_open())
			// 	std::cerr << "Error opening file -> data.csv" << std::endl;
	BitcoinExchange.file_handling("data.csv");

	// OLD // extract_rates_database(rates_database, bitrates);
	BitcoinExchange.extract_rates_database();

	// OLD // rates_database.close();

	// for (std::map<std::string, float>::iterator iter = bitrates.begin(); iter != bitrates.end(); iter++) {
	// 	std::cout << iter->first << ", " << iter->second << std::endl;
	// }

	// OLD	// std::ifstream values_database(argv[1]);
			// if (!values_database.is_open())
			// 	std::cerr << "Error opening file -> " << argv[1] << std::endl;
	BitcoinExchange.file_handling(argv[1]);

	// OLD	// extract_values_database(values_database, bitrates);
	BitcoinExchange.extract_values_database();

	return (0);
}
