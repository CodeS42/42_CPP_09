#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <list>
# include <algorithm>
# include <string>
# include <cstring>
# include <cctype>
# include <cstddef>
# include <cstdlib>
# include <limits>

class RPN
{
    private:
        enum FormulaCharacters
        {
            INVALID_INPUT = -3,
            SPACE,
            OPERAND,
            BINARY_OPERATOR
        };

        std::stack<int, std::list<int> > operands;
        std::string formula;
        RPN();
        RPN(const RPN& obj);
        RPN& operator=(const RPN& other);
    
    public:
        RPN(std::string input);
        ~RPN();
        bool isOperator(char c);
        int calculate();
        int checkResult(char sign, int nb1, int nb2);

        enum CalculationResult
        {
            OVERFLOW = -2,
            UNDERFLOW,
            DIVIDE_BY_ZERO,
            VALID_RESULT
        };
};

#endif