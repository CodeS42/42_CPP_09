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

    RPN calculation(argv[1]);
    int calculation_status = calculation.calculate();

    if (calculation_status != RPN::VALID_RESULT)
    {
        if (calculation_status == RPN::DIVIDE_BY_ZERO)
            return (error("Error: Division by zero is invalid."));
        else if (calculation_status == RPN::OVERFLOW)
            return (error("Error: Overflow."));
        else if (calculation_status == RPN::UNDERFLOW)
            return (error("Error: Underflow."));
        else
            return (error("Error: Invalid input."));
    }
    
    return (0);
}