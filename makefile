CC = cc 

CFLAGS = -Wall -Wextra -Werror -g3

# SRC = $(wildcard ./parsing/*.c) $(wildcard ./libft_torename/*.c)

SRC = $(wildcard ./*/*.c)

OBJ = $(SRC:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ -lreadline 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SECONDARY: $(OBJ)