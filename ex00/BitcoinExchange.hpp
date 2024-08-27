
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <sstream>
#include <iomanip> // for setw and setfill
#include <ctime>
#include <cstring>
#include <exception>
#include <limits>

class BitcoinExchange
{
    private:
        // BitcoinExchange();
        // BitcoinExchange(const BitcoinExchange& other);
        // BitcoinExchange& operator=(const BitcoinExchange& other);
        // ~BitcoinExchange();
        std::map<std::string, float>    bitrates;
        std::ifstream                   rates_database;
        std::ifstream                   values_database;
    public:
        class   InvalidDateFormat;
        class   AmbigousDate;
        class   DateTooOld;
        class   InvalidDate;
        class   MissingRate;
        class   ValueTooLarge;
        class   NegativeValue;
        class   InvalidRate;
        void    file_handling(const char* filename);
        void	extract_rates_database();
        void    extract_values_database();
};

class BitcoinExchange::InvalidDateFormat : public std::exception {
    const char* what() const throw();
};

class BitcoinExchange::AmbigousDate : public std::exception {
    const char* what() const throw();
};

class BitcoinExchange::DateTooOld : public std::exception {
    const char* what() const throw();
};

class BitcoinExchange::InvalidDate : public std::exception {
    const char* what() const throw();
};

class BitcoinExchange::MissingRate : public std::exception {
    const char* what() const throw();
};

class BitcoinExchange::ValueTooLarge : public std::exception {
    const char* what() const throw();
};

class BitcoinExchange::NegativeValue : public std::exception {
    const char* what() const throw();
};

class BitcoinExchange::InvalidRate : public std::exception {
    const char* what() const throw();
};

std::string trim(const std::string& str);
std::string	get_new_date(std::string& date);
void	    parse_date(std::string& date);
float	    parse_rate(std::string& rate);

#endif