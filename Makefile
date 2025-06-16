NAME = philo

SRC = parcing.c  philo.c utils.c routine.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(CFLAGS) $^ -o $(NAME) -lreadline


%.o: %.c $(HEADER)
	$(CC)  $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all