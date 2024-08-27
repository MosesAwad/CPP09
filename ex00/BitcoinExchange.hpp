
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <sstream>
#include <iomanip> // for setw and setfill

class BitcoinExchange
{
    private:
        std::map<std::string, float>    bitrates;
        std::ifstream                   rates_database;
        std::ifstream                   values_database;
    public:
        void    file_handling(const char* filename);
        void	extract_rates_database();
        void    extract_values_database();
};

std::string trim(const std::string& str);
std::string	get_new_date(std::string& date);

#endif