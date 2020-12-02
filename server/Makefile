# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/14 12:47:29 by aashara           #+#    #+#              #
#    Updated: 2020/12/02 19:19:21 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------  PROJECT  ----------------------------------------------------- #
NAME	=		FileServer

# ------------  DIRECTORIES  ------------------------------------------------- #
SRC_DIR	=		src
HDR_DIR	=		includes
OBJ_DIR	=		objs

# ------------  SOURCE FILES  ------------------------------------------------ #
SRC_FLS	=

# ------------  FILEPATHS  --------------------------------------------------- #
SRCS	=		$(addprefix $(SRC_DIR)/, $(SRC_FLS))
OBJS	=		$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o, $(SRCS))
DEPS	=		$(OBJS:.o=.d)

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		g++
RM		=		rm -rf
CFLGS	=		-Wall -Werror -Wextra -std=c++1z
LFLGS	=
IFLGS	=		-I $(HDR_DIR)
DFLGS	=		-MMD -MP
OFLGS	=		-O0 -g

# ------------  RULES  ------------------------------------------------------- #
.PHONY: all clean fclean re

all: $(NAME)

-include $(DEPS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLGS) $(DFLGS) $(OFLGS) -c -o $@ $< $(IFLGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLGS)

clean:
	$(RM) $(OBJ_DIR)

fclean:
	$(RM) $(OBJ_DIR)
	$(RM) $(NAME)

re: fclean all
