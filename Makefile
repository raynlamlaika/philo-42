NAME = philo
SRC= philo.c utils/ft_atoi.c utils/ft_itoa.c utils/ft_strncmp.c parsing.c
OBJ = ${SRC:.c=.o}


all: ${NAME}



$(NAME): $(OBJ)
	$(CC) $(OBJ) -fsanitize=address -o $(NAME)



clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all