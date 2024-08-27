
#include "BitcoinExchange.hpp"

void    BitcoinExchange::file_handling(const char* filename)
{
	std::string str(filename);

	if (str == "data.csv") {
		rates_database.open(filename);
		if (!rates_database.is_open())
		{
			std::cerr << "Error opening file -> data.csv" << std::endl;
			exit (1);
		}
	}
	else {
		values_database.open(filename);
		if (!values_database.is_open())
		{
			std::cerr << "Error opening file -> " << filename << std::endl;
			exit (1);
		}
	}

}

void	BitcoinExchange::extract_rates_database()
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

	rates_database.close();
}

bool	parse_date(std::string& date)
{
	struct tm tm;

	memset(&tm, 0, sizeof(tm));
	char* return_str = strptime(date.c_str(), "%Y-%m-%d", &tm);

	std::map<int, int> daysInMonth;

	daysInMonth[0] = 31;
	daysInMonth[1] = 28;
	daysInMonth[2] = 31;
	daysInMonth[3] = 30;
	daysInMonth[4] = 31;
	daysInMonth[5] = 30;
	daysInMonth[6] = 31;
	daysInMonth[7] = 31;
	daysInMonth[8] = 30;
	daysInMonth[9] = 31;
	daysInMonth[10] = 30;
	daysInMonth[11] = 31;

	// Leap year check

	if ((tm.tm_year % 4 == 0 && tm.tm_year % 100 != 0) || (tm.tm_year % 400 == 0))
        daysInMonth[1] = 29;

	if (return_str == NULL)
		return (std::cout << "Invalid date format" << std::endl, false);

	if (*return_str != '\0')
		return (std::cout << "Ambiguous trailors after date" << std::endl, false);

	if (tm.tm_year < 109 || (tm.tm_year == 109 && tm.tm_mon == 0 && tm.tm_mday < 2))
		return (std::cout << "Date too old" << std::endl, false);

	if ((tm.tm_mon < 0 || tm.tm_mon > 11) || (tm.tm_mday < 1 || tm.tm_mday > 31))
		return (std::cout << "Invalid date" << std::endl, false);
	
	if (tm.tm_mday > daysInMonth[tm.tm_mon])
		return (std::cout << "Invalid date" << std::endl, false);

	std::cout << tm.tm_year << "-" << tm.tm_mon << "-" << tm.tm_mday << std::endl;
	return (true);
}

void BitcoinExchange::extract_values_database()
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
		parse_date(date);
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

std::string trim(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t\n\r\f\v");
	size_t last = str.find_last_not_of(" \t\n\r\f\v");
	return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
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
