#include "../headers/RPN.hpp"

RNP::RNP(){}

RNP::RNP(std::string input) : formula(input) {}

RNP::RNP(const RNP& obj)
{
    (void)obj;
}

RNP& RNP::operator=(const RNP& other)
{
    (void)other;
    return (*this);
}

RNP::~RNP(){}

bool RNP::isOperator(char c)
{
    if (c != '+' && c != '-' && c != '*' && c != '/')
        return (false);
    return (true);
}

bool RNP::calculate()
{
    std::size_t i, size = formula.size();
    int nb1, nb2, last = SPACE;

    for (i = 0 ; i < size ; i++)
    {
        if ((isdigit(formula[i]) || isOperator(formula[i])) && last != SPACE)
            return (false);
        else if (isdigit(formula[i]))
        {
            operands.push(formula[i] - '0');
            last = OPERAND;
        }
        else if (isOperator(formula[i]))
        {
            if (i < size - 1)
            {
                if (formula[i] == '-' && isdigit(formula[i + 1]))
                {
                    operands.push(atoi(formula.substr(i, 2).c_str()));
                    i++;
                    last = OPERAND;
                    continue;
                }
            }
            if (operands.size() < 2)
                return (false);
            nb2 = operands.top();
            operands.pop();
            nb1 = operands.top();
            operands.pop();
            if (formula[i] == '+')
                operands.push(nb1 + nb2);
            else if (formula[i] == '-')
                operands.push(nb1 - nb2);
            else if (formula[i] == '*')
                operands.push(nb1 * nb2);
            else if (formula[i] == '/')
                operands.push(nb1 / nb2);
            last = BINARY_OPERATOR;
        }
        else if (isspace(formula[i]))
            last = SPACE;
        else
            return (false);
    }
    if (operands.size() != 1)
        return (false);
        
    std::cout << "Result: " << operands.top() << std::endl;
    return (true);
}
