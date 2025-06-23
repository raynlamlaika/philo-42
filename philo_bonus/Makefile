NAME = philo_bonus

SRC = child_routine.c  parcing.c  philo.c  starting_b.c  ulils.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -g

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