NAME	=		libtransfer.a

# ------------  DIRECTORIES  ------------------------------------------------- #
SRC_DIR	=		src
HDR_DIR	=		includes
OBJ_DIR	=		objs
LIB_DIR =		..


# ------------  LIBNETWORK  ------------------------------------------------- #
LNET		=		libnetwork.a
LNET_DIR	=		$(LIB_DIR)/libnetwork
LHS_NET_DIR	=		$(LNET_DIR)/includes


# ------------  SOURCE FILES  ------------------------------------------------ #
SRC_FLS	=	CRC.cpp\
					Datagram.cpp\
					File.cpp\
					Header.cpp\



# ------------  FILEPATHS  --------------------------------------------------- #
SRCS	=		$(addprefix $(SRC_DIR)/, $(SRC_FLS))
OBJS	=		$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS	=		$(OBJS:.o=.d)

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		g++
RM		=		rm -rf
CFLGS	=		-Wall -Wextra -Werror -std=c++1z
LFLGS	=		-L $(LNET_DIR) -lnetwork
IFLGS	=		-I $(HDR_DIR) -I $(LHS_NET_DIR)
DFLGS	=		-MMD -MP
OFLGS	=		-O0 -g


# ------------  RULES  ------------------------------------------------------- #
.PHONY: all clean fclean re

all: lib $(NAME)

lib:
	$(MAKE) -C $(LNET_DIR)

$(LNET_DIR)/$(LNET):
	$(MAKE) -C $(LNET_DIR)

-include $(DEPS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLGS) $(DFLGS) $(OFLGS) -c -o $@ $< $(IFLGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(LNET_DIR)/$(LNET) $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	$(MAKE) -C $(LNET_DIR) clean
	$(RM) $(OBJ_DIR)

fclean:
	$(MAKE) -C $(LNET_DIR) fclean
	$(RM) $(OBJ_DIR)
	$(RM) $(NAME)

re: fclean all
