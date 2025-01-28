NAME = push_swap

SOURCE = ft_split.c helper_instra.c prace.c putstr.c stack_oper_three.c \
         stack_opr_tow.c helper_instra2.c linkedlist.c push_swap.c \
         sort_big_stack.c stack_opperations.c utils.c ft_itoa.c

BONUSOURCE = push_swap_bonus/prace_bonus.c push_swap_bonus/bonus_helper_bonus.c \
             push_swap_bonus/check1_bonus.c push_swap_bonus/putstr_bonus.c \
             push_swap_bonus/stack_oper_three_bonus.c push_swap_bonus/ft_split_bonus.c \
             push_swap_bonus/stack_opperations_bonus.c push_swap_bonus/get_next_line_bonus.c \
             push_swap_bonus/stack_opr_tow_bonus.c push_swap_bonus/get_next_line_utils_bonus.c \
             push_swap_bonus/utils_bonus.c push_swap_bonus/linkedlist_bonus.c push_swap_bonus/bonus.c \
             push_swap_bonus/ft_itoa_bonus.c 

BNAME = checker

CC = cc

CFLAGS = -Wall -Werror -Wextra

HEADER = push_swap.h

HEADERFILEB= push_swap_bonus/push_swap_bonus.h

OBJF = $(SOURCE:.c=.o)

BOBJF = $(BONUSOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJF)
	$(CC) $(CFLAGS) $^ -o $(NAME)

bonus: $(BNAME)

$(BNAME): $(BOBJF)
	$(CC) $(CFLAGS) $^ -o $(BNAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

%bonus.o: %bonus.c $(HEADERFILEB)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJF) $(BOBJF)

fclean: clean
	rm -f $(NAME) $(BNAME)

re: fclean all


.PHONY: clean