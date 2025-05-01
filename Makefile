
CC = cc
NAME = philo
NAME_TSAN = philo_tsan
SRC = main.c utils.c utils_two.c check.c simulator.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -Wall -Wextra -Werror -g -pthread -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
