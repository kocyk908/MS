# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: piotr <piotr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 11:38:50 by pruszkie          #+#    #+#              #
#    Updated: 2024/05/20 13:23:14 by piotr            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = ft_isalnum.c \
        ft_isalpha.c \
        ft_isascii.c \
        ft_isdigit.c \
        ft_isprint.c \
        ft_strchr.c \
        ft_strlcat.c \
        ft_strlcpy.c \
        ft_strlen.c \
        ft_strncmp.c \
        ft_strnstr.c \
        ft_strrchr.c \
        ft_memset.c \
        ft_memcpy.c \
        ft_bzero.c \
        ft_memmove.c \
        ft_toupper.c \
        ft_tolower.c \
        ft_memchr.c \
        ft_memcmp.c \
        ft_atoi.c \
        ft_calloc.c \
        ft_strdup.c \
        ft_substr.c \
        ft_strjoin.c \
        ft_strtrim.c \
        ft_itoa.c \
        ft_strmapi.c \
        ft_striteri.c \
        ft_putchar_fd.c \
        ft_putstr_fd.c \
        ft_putendl_fd.c \
        ft_putnbr_fd.c \
	ft_strcpy.c \
	ft_strcat.c \
	ft_strcmp.c \
        **ft_split.c
OBJ = $(FILES:.c=.o)

BONUS = ft_lstadd_front.c \
        ft_lstadd_back.c \
        ft_lstnew.c \
        ft_lstsize.c \
        ft_lstlast.c \
        ft_lstdelone.c \
        ft_lstclear.c \
        ft_lstiter.c \
        ft_lstmap.c

BONUS_OBJS		= $(BONUS:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = libft.a

NAME			= libft.a

all:			$(NAME)

$(NAME):		$(OBJ)
				ar rcs $(NAME) $(OBJ)

clean:
				$(RM) $(OBJ) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

bonus:			$(OBJ) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJ) $(BONUS_OBJS)

.PHONY:			all clean fclean re bonus
