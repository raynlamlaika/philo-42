NAME = philo
SRC= philo.c utils/ft_atoi.c utils/ft_itoa.c utils/ft_strncmp.c parsing.c helpers.c \
		philosophers.c
OBJ = ${SRC:.c=.o}


all: ${NAME}


$(NAME): $(OBJ)
	$(CC) -fsanitize=thread  $(OBJ)  -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -fsanitize=thread -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all