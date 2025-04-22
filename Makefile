NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_DIR = mandatory/srcs
INC_DIR = mandatory/includes
LIB_DIR = $(SRC_DIR)/lib
UTILS_DIR = $(SRC_DIR)/utils

SRCS = $(SRC_DIR)/pipex.c \
	   $(LIB_DIR)/ft_split.c \
	   $(LIB_DIR)/ft_strdup.c \
	   $(LIB_DIR)/ft_strjoin.c \
	   $(LIB_DIR)/ft_strlen.c \
	   $(LIB_DIR)/ft_strncmp.c \
	   $(LIB_DIR)/ft_strtok.c \
	   $(UTILS_DIR)/error_handling.c \
	   $(UTILS_DIR)/pipex_utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -I$(INC_DIR) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re