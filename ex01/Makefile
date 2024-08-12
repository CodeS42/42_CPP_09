SRCS =  srcs/main.cpp \
		srcs/RPN.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

INCLUDES = headers

NAME = RPN

FLAGS = -Wall -Wextra -Werror -std=c++98

.cpp.o :
	c++ $(FLAGS) -I $(INCLUDES) -MMD -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	c++ $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS) $(DEPS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

-include $(DEPS)