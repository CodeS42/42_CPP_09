#ifndef RNP_HPP
# define RNP_HPP

# include <iostream>
# include <stack>
# include <list>
# include <algorithm>
# include <string>
# include <cstring>
# include <cctype>
# include <cstddef>
# include <cstdlib>

class RNP
{
    private:
        enum Character
        {
            SPACE,
            OPERAND,
            BINARY_OPERATOR
        };

        std::stack<int, std::list<int> > operands;
        std::string formula;
        RNP();
        RNP(const RNP& obj);
        RNP& operator=(const RNP& other);
    
    public:
        RNP(std::string input);
        ~RNP();
        bool isOperator(char c);
        bool calculate();
};

#endif