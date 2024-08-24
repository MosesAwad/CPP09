
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>

int main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;

	std::ifstream database("data.csv");

	if (!database.is_open())
		std::cerr << "Error opening file -> data.csv" << std::endl;

	std::map<std::string, float> bitrates;
	
	std::string	header;
	std::getline(database, header);
	while () {
		std::string date;
		std::string	rate;

		std::getline(database, date, ',');
		std::getline(database, rate);
		bitrates[date] = atof(rate.c_str());
	}
	database.close();

	// for (std::map<std::string, float>::iterator iter = bitrates.begin(); iter != bitrates.end(); iter++) {
	// 	std::cout << iter->first << ", " << iter->second << std::endl;
	// }

	return (0);
}
