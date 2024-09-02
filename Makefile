NAME	=	minishell
# CC		=	gcc -Wall -Wextra -Werror
CC		= 	gcc
CFLAGS	=	-g -I include 

SRCS = $(wildcard src/*.c)

# SRCS	=	src/main.c src/exe_pipeline_utils.c src/execute_pipeline.c src/parsing.c src/execute_builtin.c src/path_finding.c src/parsing_utils.c src/redirections.c src/env.c src/signals.c

LIBFT	=	$(wildcard libft/*.c)

OBJS	=	$(SRCS:.c=.o) $(LIBFT:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re

