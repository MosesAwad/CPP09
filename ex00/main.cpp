
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <sstream>

std::string trim(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t\n\r\f\v");
	size_t last = str.find_last_not_of(" \t\n\r\f\v");
	return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

void	extract_rates_database(std::ifstream& rates_database, std::map<std::string, float>& bitrates)
{
	std::string	header;
	std::getline(rates_database, header);

	while (rates_database.good()) {
		std::string date;
		std::string	rate;

		std::getline(rates_database, date, ',');
		if (date.empty())
			continue ;
		std::getline(rates_database, rate);
		bitrates[date] = atof(rate.c_str());
	}
}

std::string	get_new_date(std::string& date)
{
	int year = atoi(date.substr(0, 4).c_str());
	int month = atoi(date.substr(5, 2).c_str());
	int day = atoi(date.substr(8, 2).c_str());

	if (year < 2009 || (year == 2009 && month == 1 && day == 1))
		return ("date_too_old");

	std::ostringstream oss;
	std::string new_date;
	if (day > 1)
		day--;
	else
	{
		day = 31;
		if (month > 1)
			month--;
		else
		{
			day = 31;
			month = 12;
			year--;
		}
	}
	oss << year;
	new_date = oss.str();
	oss.str(""); // Clear the stream
	oss.clear(); // Clear any flags
	
	new_date += '-';
	oss << std::setw(2) << std::setfill('0') << month;
	new_date += oss.str();
	oss.str(""); // Clear the stream
	oss.clear(); // Clear any flags

	new_date += '-';
	oss << std::setw(2) << std::setfill('0') << day;
	new_date += oss.str();
	oss.str(""); // Clear the stream
	oss.clear(); // Clear any flags

	return (new_date);
}

void extract_values_database(std::ifstream& values_database, std::map<std::string, float>& bitrates)
{
	std::string header;

	std::getline(values_database, header);
	while (values_database.good())
	{
		std::string date;
		std::string	rate;
		std::map<std::string, float>::iterator element;

		// get date
		std::getline(values_database, date, '|');
		date = trim(date);
		while (bitrates.find(date) == bitrates.end())
		{
			date = trim(get_new_date(date));
			if (date == "date_too_old")
				return (std::cerr << "Invalid entry, date too old" << std::endl, void());
		}

		std::cout << date << std::endl;

		// get rate
		std::getline(values_database, rate);
	}
}

int main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;

	std::ifstream rates_database("data.csv");
	if (!rates_database.is_open())
		std::cerr << "Error opening file -> data.csv" << std::endl;

	std::map<std::string, float> bitrates;
	extract_rates_database(rates_database, bitrates);
	rates_database.close();

	for (std::map<std::string, float>::iterator iter = bitrates.begin(); iter != bitrates.end(); iter++) {
		std::cout << iter->first << ", " << iter->second << std::endl;
	}

	std::ifstream values_database(argv[1]);
	if (!values_database.is_open())
		std::cerr << "Error opening file -> " << argv[1] << std::endl;
	extract_values_database(values_database, bitrates);
	return (0);
}
