# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sojung <sojung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/29 12:45:44 by sojung            #+#    #+#              #
#    Updated: 2022/10/31 14:05:31 by sojung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# make -j5 (make with 5 threads)
# make -j$(nproc) : substitute nproc with the number of cores of machine
# (number of core + 1) is the fastest in general!

NAME = ft_containers

NAME2 = std_containers

CC = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

INCLUDE = -Iinclude/

SRC_DIR = ./src
SRC_STD_DIR = ./src_std

OBJ_DIR = ./obj
OBJ_STD_DIR = ./obj_std

SRCS = $(notdir $(wildcard $(SRC_DIR)/*.cpp))
SRCS_STD = $(notdir $(wildcard $(SRC_STD_DIR)/*.cpp))

OBJS = $(SRCS:.cpp=.o)
OBJS_STD = $(SRCS_STD:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

#$(patsubst PATTERN, POST_SUBSTITUTE_FORM, VARIABLE)
OBJECTS = $(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))
OBJECTS_STD = $(patsubst %.o,$(OBJ_STD_DIR)/%.o,$(OBJS_STD))
DEPS = $(OBJECTS:.o=.d)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ -MD

$(OBJ_STD_DIR)/%.o : $(SRC_STD_DIR)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

all : ft_containers std_containers

$(NAME) : $(OBJECTS)
	$(CC) $(CXXFLAGS) $(OBJECTS) -o $@

$(NAME2) : $(OBJECTS_STD)
	$(CC) $(CXXFLAGS) $(OBJECTS_STD) -o $@

clean :
	rm -f $(OBJECTS) $(OBJECTS_STD) $(DEPS)

fclean : clean
	rm -f $(NAME) $(NAME2)

re : fclean all

-include $(DEPS)

.PHONY : all clean fclean re