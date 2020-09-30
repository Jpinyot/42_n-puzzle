# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/24 19:02:13 by jpinyot           #+#    #+#              #
#    Updated: 2020/09/30 10:28:36 by mfiguera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = n-puzzle

#FLAGS = -Wall -Wextra -Werror
FLAGS =

SRCS_DIR = srcs/

SRCS = state.cpp\
       stateManhattanDistance.cpp\
       main.cpp\
	   closedStack.cpp\

OBJ_SRCS = $(patsubst %.cpp, $(SRCS_DIR)%.o, $(SRCS))

OBJ = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ_SRCS)
	@g++ $(FLAGS) -I./srcs/*.h $(OBJ) -o $(NAME)

%.o : %.cpp
	@g++ $(FLAGS) -I./srcs/*.h -c $<

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean
	@make

.PHONY: all clean fclean re
