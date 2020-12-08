# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/14 12:47:29 by aashara           #+#    #+#              #
#    Updated: 2020/12/08 14:37:35 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------  PROJECT  ----------------------------------------------------- #
NAME	=		../FileClient

# ------------  DIRECTORIES  ------------------------------------------------- #
SRC_DIR	=		src
HDR_DIR	=		includes
OBJ_DIR	=		objs
LIB_DIR =		../lib

# ------------  SOURCE FILES  ------------------------------------------------ #
SRC_FLS	= createFiles.cpp\
					main.cpp\
					sendDatagram.cpp\
					sendFiles.cpp\


# ------------  LIBNETWORK  ------------------------------------------------- #
LNET		=		libnetwork.a
LNET_DIR	=		$(LIB_DIR)/libnetwork
LHS_NET_DIR	=		$(LNET_DIR)/includes

# ------------  LIBTRANSFER  ------------------------------------------------- #
LTRANS		=		libtransfer.a
LTRANS_DIR	=		$(LIB_DIR)/libtransfer
LHS_TRANS_DIR	=		$(LTRANS_DIR)/includes


# ------------  FILEPATHS  --------------------------------------------------- #
SRCS	=		$(addprefix $(SRC_DIR)/, $(SRC_FLS))
OBJS	=		$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o, $(SRCS))
DEPS	=		$(OBJS:.o=.d)

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		g++
RM		=		rm -rf
CFLGS	=		-Wall -Werror -Wextra -std=c++1z
LFLGS	=		 -L $(LTRANS_DIR) -ltransfer -L $(LNET_DIR) -lnetwork
IFLGS	=		-I $(HDR_DIR) -I $(LHS_NET_DIR) -I $(LHS_TRANS_DIR)
DFLGS	=		-MMD -MP
OFLGS	=		-O0 -g

# ------------  RULES  ------------------------------------------------------- #
.PHONY: all clean fclean re

all: lib $(NAME)

lib:
	$(MAKE) -C $(LNET_DIR)
	$(MAKE) -C $(LTRANS_DIR)

$(LTRANS_DIR)/$(LTRANS):
	$(MAKE) -C $(LTRANS_DIR)

$(LNET_DIR)/$(LNET):
	$(MAKE) -C $(LNET_DIR)

-include $(DEPS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLGS) $(DFLGS) $(OFLGS) -c -o $@ $< $(IFLGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(LNET_DIR)/$(LNET) $(LTRANS_DIR)/$(LTRANS) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLGS)

clean:
	$(MAKE) -C $(LTRANS_DIR) clean
	$(MAKE) -C $(LNET_DIR) clean
	$(RM) $(OBJ_DIR)

fclean:
	$(MAKE) -C $(LTRANS_DIR) fclean
	$(MAKE) -C $(LNET_DIR) fclean
	$(RM) $(OBJ_DIR)
	$(RM) $(NAME)

re: fclean all
