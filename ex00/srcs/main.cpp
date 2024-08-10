#include "../headers/BitcoinExchange.hpp"

int error(std::string error_msg)
{
    std::cerr << error_msg << std::endl;
    return (1);
}

void skipSpaces(std::size_t& i, std::string& line, std::size_t& size)
{
    while (i < size && isspace(line[i]))
        i++;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
        return (error("Error: Wrong number of arguments"));

    std::ifstream input_file(argv[1], std::ios::in);
    std::ifstream data_file("data.csv", std::ios::in);

    if (!input_file.is_open())
        return (error("Error: Failed to open file"));
    if (!data_file.is_open())
    {
        input_file.close();
        return (error("Error: Failed to open file"));
    }

    BitcoinExchange bitcoin(data_file);

    bitcoin.exchange(input_file);

    return (0);
}