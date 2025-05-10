
CC = cc
NAME = philo
SRC = main.c utils.c utils_two.c check.c simulator.c ft_clean.c
OBJ = $(SRC:.c=.o)
#-fsanitize=thread
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -Wall -Wextra -Werror -g  -pthread -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
