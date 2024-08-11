#include "../headers/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& obj)
{
    (void)obj;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    (void)other;
    return (*this);
}

BitcoinExchange::BitcoinExchange(std::ifstream& _datafile)
{
    fillDataContainer(_datafile);
}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::Value::Value(int _nb)
{
    nb.int_nb = _nb;
    nb_type = INT;
}

BitcoinExchange::Value::Value(float _nb)
{
    nb.float_nb = _nb;
    nb_type = FLOAT;
}

void BitcoinExchange::fillDataContainer(std::ifstream& _file)
{
    std::string key, value, line;
    std::size_t i, pos;

    while (std::getline(_file, line))
    {
        pos = line.find(',');
        key = "";
        value = "";
        
        for (i = 0 ; i < pos ; i++)
            key += line[i];
        while (++i < line.size())
            value += line[i];

        if (isFloat(value))
        {
            float float_nb = atof(value.c_str());
            data.insert(std::make_pair(key, Value(float_nb)));
        }
        else if (isInt(value))
        {
            int int_nb = atoi(value.c_str());
            data.insert(std::make_pair(key, Value(int_nb)));
        }
    }
}

bool BitcoinExchange::checkDate(std::string& line)
{
    std::size_t  i = 0, size = line.size();
    struct tm tm;
    int year, month, day, days_per_month[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    skipSpaces(i, line, size);
    if (line.substr(i).size() < 10)
        return (false);
    if (!strptime(line.substr(i, 10).c_str(), "%Y-%m-%d", &tm))
        return (false);

    year = atoi(line.substr(i, 4).c_str());
    month = atoi(line.substr(i + 5, 2).c_str());
    day = atoi(line.substr(i + 8, 2).c_str());

    if (day < 1 || day > days_per_month[month - 1]
        || month < 1 || month > 12 
        || (month == 2 && day == 29 && !isLeapYear(year)))
        return (false);
    
    return (true);
}

int BitcoinExchange::checkValue(std::string line)
{
    std::size_t  i = 0, size = line.size();
    std::string value;

    skipSpaces(i, line, size);
    if (i == size)
        return (INVALID_NUMBER);
    while (i < size && !isspace(line[i]))
        value += line[i++];
    if (isInt(value))
    {
        long int_nb = std::strtol(value.c_str(), NULL, 10);

        if (int_nb > 1000)
            return (TOO_LARGE);
        else if (int_nb < 0)
            return (NEGATIVE_NUMBER);
        return (INT);
    }
    else if (isFloat(value))
    {
        float float_nb = atof(value.c_str());
        
        if (float_nb > 1000)
            return (TOO_LARGE);
        else if (float_nb < 0)
            return (NEGATIVE_NUMBER);
        return (FLOAT);
    }
    else
        return (INVALID_NUMBER);
}

int BitcoinExchange::checkInput(std::string& line)
{
    std::size_t pos;
    int value;

    pos = line.find('|');

    if (!checkDate(line))
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return (INVALID_INPUT);
    }
    if (pos == std::string::npos)  
    {
        std::cerr << "Error: “|” missing" << std::endl;
        return (INVALID_INPUT);
    }

    value = checkValue(line.substr(pos + 1));

    if (value == INVALID_NUMBER || value == NEGATIVE_NUMBER || value == TOO_LARGE)
    {
        if (value == INVALID_NUMBER)
            std::cerr << "Error: bad input => " << line << std::endl;
        else if (value == NEGATIVE_NUMBER)
            std::cerr << "Error: not a positive number." << std::endl;
        else if (value == TOO_LARGE)
            std::cerr << "Error: too large a number." << std::endl;
        return (INVALID_INPUT);
    }
    
    return (value);
}

bool BitcoinExchange::checkInputFirstLine(std::ifstream& _inputfile, std::string& line, std::size_t& size, std::size_t& i)
{
    i = 0;
    std::getline(_inputfile, line);
    size = line.size();

    skipSpaces(i, line, size);
    if (line.substr(i, 4) != "date")
        return (false);
    i += 4;
    skipSpaces(i, line, size);
    if (line[i] != '|')
        return (false);
    i++;
    skipSpaces(i, line, size);
    if (line.substr(i, 5) != "value")
        return (false);
    i += 5;
    skipSpaces(i, line, size);
    if (i < size)
        return (false);
    return (true);  
}

void BitcoinExchange::exchange(std::ifstream& _inputfile)
{
    std::string line, value, substring;
    std::size_t i, size;
    map::iterator it;
    int input;

    if (!checkInputFirstLine(_inputfile, line, size, i))
    {
        std::cerr << "Error: First line of input is invalid." << std::endl;
        return ;
    }
    while (std::getline(_inputfile, line))
    {
        input = checkInput(line);

        if (input != INVALID_INPUT)
        {
            i = 0;
            size = line.size();

            skipSpaces(i, line, size);

            substring = line.substr(i, 10);

            it = data.lower_bound(substring);
            if (it == data.begin() && it->first != substring)
            {
                std::cerr << "Error: No match for this date." << std::endl;
                continue;
            }
            else if (it == data.end() || it->first != substring)
                it--;

            i = line.find('|');

            i++;
            skipSpaces(i, line, size);
            for (value = "" ; i < size && !isspace(line[i]) ; i++)
                value += line[i];
            std::cout << substring << " => " << value << " = ";
        
            if (input == INT)
            {
                if (it->second.nb_type == INT)
                    std::cout << atoi(value.c_str()) * it->second.nb.int_nb << std::endl;
                else if (it->second.nb_type == FLOAT)
                    std::cout << atoi(value.c_str()) * it->second.nb.float_nb << std::endl;
            }
            else if (input == FLOAT)
            {
                if (it->second.nb_type == INT)
                    std::cout << atof(value.c_str()) * it->second.nb.int_nb << std::endl;
                else if (it->second.nb_type == FLOAT)
                    std::cout << atof(value.c_str()) * it->second.nb.float_nb << std::endl;
            }
        }
    }
}

bool BitcoinExchange::isFloat(std::string& nb)
{
	std::size_t string_size = nb.size(), i = 0;

	if (!isdigit(nb[0]) && nb[0] != '-' && nb[0] != '+')
		return (false);
	if (nb[0] != '-' || nb[0] != '+')
		i++;
	while (i < string_size)
	{
		if (nb[i] == '.')
			break;
		else if (!isdigit(nb[i]))
			return (false);
		i++;
	}
	if ((nb[i] != '.') || (nb[i] == '.' && (i + 1) == string_size))
		return (false);
	while(++i < string_size)
	{
		if (!isdigit(nb[i]))
			return (false);
	}
	return (true);
}

bool BitcoinExchange::isInt(std::string& nb)
{
	std::size_t i = 0;

	if (!isdigit(nb[0]) && nb[0] != '-' && nb[0] != '+')
		return (false);
	if (nb[0] != '-' || nb[0] != '+')
		i++;
	while (i < nb.size())
	{
		if (!isdigit(nb[i]))
			return (false);
		i++;
	}
	return (true);
}

bool BitcoinExchange::isLeapYear(int& year)
{
    if (year % 4 == 0) 
    {
        if (year % 100 == 0) 
            return (year % 400 == 0);
        return true;
    }
    return false;
}