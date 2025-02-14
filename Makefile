SRC = main.c general_utils.c parsing_input.c \
	  threads_cicle.c threads_cicle_2.c
OBJ = $(SRC:.c=.o)
CC = cc
COMPILER_FLAGS = -g -Wall -Wextra -Werror
NAME = philosophers

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(COMPILER_FLAGS) -o $(NAME) $(OBJ)

%.o: %.c philosophers.h
	$(CC) $(COMPILER_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean
