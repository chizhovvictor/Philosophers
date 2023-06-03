NAME = philo

SRCS =	philo.c utils.c init.c

HEADER = ./mandatory/include/

OBJS = $(SRCS:.c=.o)

CFLAGS = -Werror -Wextra -Wall #-fsanitize=thread -g 

all: $(NAME)

CC = cc

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) -I $(HEADER) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread


clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(OBJS) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re bonus
