#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <iostream>
# include <string>
# include <cstring>
# include <algorithm>
# include <map>
# include <fstream>
# include <cctype>
# include <ctime>
# include <cstddef>
# include <cstdlib>

class BitcoinExchange
{
    private:
        enum Invalid
        {
            INVALID_INPUT = -4,
            INVALID_NUMBER,
            NEGATIVE_NUMBER,
            TOO_LARGE
        };

        enum Type
        {
            INT,
            FLOAT
        };

        union IntOrFloat
        {
            int     int_nb;
            float   float_nb;
        };

        typedef struct Value
        {
            IntOrFloat  nb;
            Type        nb_type;

            Value(int _nb);
            Value(float _nb);
        }               Value;

        typedef std::map<std::string, Value> map;

        map data;
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& obj);
        BitcoinExchange& operator=(const BitcoinExchange& other);
    
    public:
        BitcoinExchange(std::ifstream& _datafile);
        ~BitcoinExchange();
        void fillDataContainer(std::ifstream& _file);
        void exchange(std::ifstream& _inputfile);
        bool checkInputFirstLine(std::ifstream& _inputfile, std::string& line, std::size_t& size, std::size_t& i);
        int checkInput(std::string& line);
        bool checkDate(std::string& line);
        bool isLeapYear(int& year);
        int checkValue(std::string line);
        bool isFloat(std::string& nb);
        bool isInt(std::string& nb);
};

void skipSpaces(std::size_t& i, std::string& line, std::size_t& size);

#endif