#include "../headers/RPN.hpp"

int error(std::string error_msg)
{
    std::cerr << error_msg << std::endl;
    return (1);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
        return (error("Error: Wrong number of arguments."));

    RNP calculation(argv[1]);

    if (!calculation.calculate())
        return (error("Error: Invalid input."));
    
    return (0);
}