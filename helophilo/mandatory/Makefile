NAME = philo

SRC = parcing.c  philo.c utils.c routine.c routine_helper.c signle_philo.c
OBJ = $(SRC:.c=.o)

CC = cc 
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(CFLAGS) $^ -o $(NAME)


%.o: %.c $(HEADER)
	$(CC)  $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all