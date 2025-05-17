CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g  -fsanitize=thread -pthread
#-fsanitize=thread
NAME    = philo

SRC     = main.c utils.c utils_two.c check.c simulator.c ft_clean.c
OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
