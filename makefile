CC = cc 

# CFLAGS = -Wall -Wextra -Werror

# SRC = $(wildcard ./parsing/*.c) $(wildcard ./libft_torename/*.c)

SRC = $(wildcard ./*/*.c)

OBJ = $(SRC:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ -lreadline 

%.o: %.c
<<<<<<< HEAD
	$(CC)  -c $< -o $@
=======
	$(CC) -c $< -o $@ 
>>>>>>> 20b2afae700ec69c7642c2d715f1e5569c116878

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SECONDARY: $(OBJ)