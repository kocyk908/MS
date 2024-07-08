NAME	= minishell
CC	= gcc
CFLAGS	= -g -I include

SRCS	= src/*.c
OBJS	= $(SRCS:.c=.o)

LIBFT	= libft/*.c

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

