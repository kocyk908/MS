CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include

SRCS = src/main.c src/display.c src/execute_pipeline.c src/parsing.c src/execute_builtin.c
OBJS = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

