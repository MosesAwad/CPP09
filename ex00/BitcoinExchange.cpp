
#include "BitcoinExchange.hpp"

const char* BitcoinExchange::InvalidDateFormat::what() const throw()
{
	return ("Invalid date format");
}

const char* BitcoinExchange::AmbigousDate::what() const throw()
{
	return ("Ambiguous trailors after date");
}

const char* BitcoinExchange::DateTooOld::what() const throw()
{
	return ("Date too old");
}

const char* BitcoinExchange::InvalidDate::what() const throw()
{
	return ("Invalid date");
}

const char* BitcoinExchange::MissingRate::what() const throw()
{
	return ("Missing rate");
}

const char* BitcoinExchange::ValueTooLarge::what() const throw()
{
	return ("Too large a number");
}

const char* BitcoinExchange::NegativeValue::what() const throw()
{
	return ("Negative value being used");
}

const char* BitcoinExchange::InvalidRate::what() const throw()
{
	return ("Invalid rate");
}

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

void BitcoinExchange::extract_values_database()
{

	std::string header;

	std::getline(values_database, header);
	while (values_database.good())
	{
		std::string	line;
		std::string date;
		std::string original_date;
		std::string	rate;
		float		f_rate;

		// Get full line entry
		std::getline(values_database, line);
		if (line.empty())
			continue ;
		size_t	delim_pos = line.find('|');
		if (delim_pos == std::string::npos) {
			std::cerr << "Error: bad input -> " << line << std::endl;
			continue ;
		}

		// Get date
		date = line.substr(0, delim_pos);
		date = trim(date);
		try {
			parse_date(date);
		}
		catch (std::exception& e) {
			std::cerr << "Error: " << e.what() << " -> " << date << std::endl;
			continue ;
		}
		original_date = date;
		while (bitrates.find(date) == bitrates.end())
			date = trim(get_new_date(date));

		// Get rate
		rate = line.substr(delim_pos + 1);
		rate = trim(rate);
		try {
			f_rate = parse_rate(rate);
		}
		catch (std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
			continue ;
		}

		// Display results
		std::cout << original_date; 
		if (date != original_date) 
			std::cout << " (" << date << ") ";
		std::cout << " -> " << rate << " = " 
				<< std::fixed << std::setprecision(2)
				<< f_rate * bitrates[date] << std::endl;
	}
	values_database.close();
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

void	parse_date(std::string& date)
{
	struct tm tm;
	memset(&tm, 0, sizeof(tm));

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
	char* return_str = strptime(date.c_str(), "%Y-%m-%d", &tm);

	if ((tm.tm_year % 4 == 0 && tm.tm_year % 100 != 0) || (tm.tm_year % 400 == 0))
        daysInMonth[1] = 29;
	if (return_str == NULL)
		throw(BitcoinExchange::InvalidDate());
	if (*return_str != '\0')
		throw(BitcoinExchange::AmbigousDate());
	if (tm.tm_year < 109 || (tm.tm_year == 109 && tm.tm_mon == 0 && tm.tm_mday < 2))
		throw(BitcoinExchange::DateTooOld());
	if ((tm.tm_mon < 0 || tm.tm_mon > 11) || (tm.tm_mday < 1 || tm.tm_mday > 31))
		throw(BitcoinExchange::InvalidDate());
	if (tm.tm_mday > daysInMonth[tm.tm_mon])
		throw(BitcoinExchange::InvalidDate());
}

float	parse_rate(std::string& rate)
{
	if (rate.empty())
		throw(BitcoinExchange::MissingRate());
	
	long long	l_result;
	char*		l_endptr;
	l_result = strtol(rate.c_str(), &l_endptr, 10);

	if (l_result > 1000)
		throw(BitcoinExchange::ValueTooLarge());
	if (l_result < 0)
		throw(BitcoinExchange::NegativeValue());
	if (*l_endptr == '\0')
		return (l_result);	
	
	double		f_result;
	char*		f_endptr;
	f_result = strtod(rate.c_str(), &f_endptr);
	
	if (f_result > 1000)
		throw(BitcoinExchange::ValueTooLarge());
	if (f_result < 0)
		throw(BitcoinExchange::NegativeValue());
	if (*f_endptr == '\0')
		return (static_cast<float>(f_result));
	throw(BitcoinExchange::InvalidRate());
}
