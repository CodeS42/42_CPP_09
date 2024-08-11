#include "../headers/RPN.hpp"

RPN::RPN(){}

RPN::RPN(std::string input) : formula(input) {}

RPN::RPN(const RPN& obj)
{
    (void)obj;
}

RPN& RPN::operator=(const RPN& other)
{
    (void)other;
    return (*this);
}

RPN::~RPN(){}

bool RPN::isOperator(char c)
{
    if (c != '+' && c != '-' && c != '*' && c != '/')
        return (false);
    return (true);
}

int RPN::checkResult(char sign, int nb1, int nb2)
{
    if (sign == '+')
    {
        if (nb2 < 0 && nb1 < std::numeric_limits<int>::min() - nb2) 
            return (UNDERFLOW);
        else if (nb2 > 0 && nb1 > std::numeric_limits<int>::max() - nb2)
            return (OVERFLOW);
    }
    else if (sign == '-')
    {
        if (nb2 > 0 && nb1 < std::numeric_limits<int>::min() + nb2)
            return (UNDERFLOW);
        else if (nb2 < 0 && nb1 > std::numeric_limits<int>::max() + nb2)
            return (OVERFLOW);
    }
    else if (sign == '*')
    {
        if (nb1 > 0)
        {
            if (nb2 < 0 && nb2 < std::numeric_limits<int>::min() / nb1)
                return (UNDERFLOW);
            else if (nb2 > 0 && nb1 > std::numeric_limits<int>::max() / nb2)
                return (OVERFLOW);
        }
        else if (nb1 < 0)
        {
            if (nb2 > 0 && nb1 < std::numeric_limits<int>::min() / nb2)
                return (UNDERFLOW);
            else if (nb2 < 0 && nb1 > std::numeric_limits<int>::max() / nb2)
                return (OVERFLOW);
        }
    }
    else if (sign == '/')
    {
        if (nb2 == 0)
            return (DIVIDE_BY_ZERO);
        else if (nb1 == std::numeric_limits<int>::min() && nb2 == -1)
            return (OVERFLOW);
    }

    return (VALID_RESULT);
}

int RPN::calculate()
{
    std::size_t i, size = formula.size(), count_nbs = 0;
    int nb1, nb2, last = SPACE, result_status;

    for (i = 0 ; i < size ; i++)
    {
        if ((isdigit(formula[i]) || isOperator(formula[i])) && last != SPACE)
            return (INVALID_INPUT);
        else if (isdigit(formula[i]))
        {
            operands.push(formula[i] - '0');
            count_nbs++;
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
                    count_nbs++;
                    last = OPERAND;
                    continue;
                }
            }
            if (operands.size() < 2)
                return (INVALID_INPUT);
            nb2 = operands.top();
            operands.pop();
            nb1 = operands.top();
            operands.pop();
            result_status = checkResult(formula[i], nb1, nb2);
            if (result_status != VALID_RESULT)
                return (result_status);
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
            return (INVALID_INPUT);
    }
    if (count_nbs < 2 || operands.size() != 1)
        return (INVALID_INPUT);
        
    std::cout << "Result: " << operands.top() << std::endl;
    return (VALID_RESULT);
}
