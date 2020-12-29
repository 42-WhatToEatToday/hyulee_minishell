# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/30 03:05:37 by hyulee            #+#    #+#              #
#    Updated: 2020/12/27 16:35:10 by hyulee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
RM = rm -f

SRCS = ./ft_memset.c \
	   ./ft_bzero.c \
	   ./ft_memcpy.c \
	   ./ft_memccpy.c \
	   ./ft_memmove.c \
	   ./ft_memchr.c \
	   ./ft_memcmp.c \
	   ./ft_strlen.c \
	   ./ft_strlcpy.c \
	   ./ft_strlcat.c \
	   ./ft_strchr.c \
	   ./ft_strrchr.c \
	   ./ft_strnstr.c \
	   ./ft_strncmp.c \
	   ./ft_strcmp.c \
	   ./ft_atoi.c \
	   ./ft_isalpha.c \
	   ./ft_isdigit.c \
	   ./ft_isalnum.c \
	   ./ft_isascii.c \
	   ./ft_isprint.c \
	   ./ft_toupper.c \
	   ./ft_tolower.c \
	   ./ft_strdup.c \
	   ./ft_strndup.c \
	   ./ft_calloc.c \
	   ./ft_substr.c \
	   ./ft_strjoin.c \
	   ./ft_strtrim.c \
	   ./ft_split.c \
	   ./ft_itoa.c \
	   ./ft_uitoa.c \
	   ./ft_strmapi.c \
	   ./ft_putchar_fd.c \
	   ./ft_putstr_fd.c \
	   ./ft_putendl_fd.c \
	   ./ft_putnbr_fd.c

SRCS_B =	./ft_lstnew.c \
			./ft_lstadd_front.c \
			./ft_lstsize.c \
			./ft_lstlast.c \
			./ft_lstadd_back.c \
			./ft_lstdelone.c \
			./ft_lstclear.c \
			./ft_lstiter.c \
			./ft_lstmap.c

SRCS_ADD = ./get_next_line.c

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)
OBJS_ADD = $(SRCS_ADD:.c=.o)

.PHONY : bonus all clean fclean re

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(OBJS_B) $(OBJS_ADD)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(OBJS_B) $(OBJS_ADD)

bonus: all

clean:
	$(RM) $(OBJS) $(OBJS_B) $(OBJS_ADD)

fclean: clean
	$(RM) $(NAME)

re: fclean all
