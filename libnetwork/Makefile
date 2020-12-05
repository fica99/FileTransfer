NAME	=		libnetwork.a

# ------------  DIRECTORIES  ------------------------------------------------- #
SRC_DIR	=		src
HDR_DIR	=		includes
OBJ_DIR	=		objs


# ------------  SOURCE FILES  ------------------------------------------------ #
SRC_FLS	=		AddrInfo.cpp\
						Bind.cpp\
						Datagram.cpp\
						Error.cpp\
						Send.cpp\
						Serialize.cpp\
						Socket.cpp\




# ------------  FILEPATHS  --------------------------------------------------- #
SRCS	=		$(addprefix $(SRC_DIR)/, $(SRC_FLS))
OBJS	=		$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS	=		$(OBJS:.o=.d)

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		g++
RM		=		rm -rf
CFLGS	=		-Wall -Wextra -Werror -std=c++1z
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
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean:
	$(RM) $(OBJ_DIR)
	$(RM) $(NAME)

re: fclean all
