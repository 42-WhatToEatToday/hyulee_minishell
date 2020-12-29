# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/21 14:46:02 by hyulee            #+#    #+#              #
#    Updated: 2020/12/27 21:47:12 by hyulee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs 
RM = rm -f

SRCS =	./ft_printf.c \
		./ft_printf_utils.c \
		./putchar_n.c \
		./convert_base.c \
		./convert_address.c \
		./print_c.c \
		./print_s.c \
		./print_d.c \
		./print_u.c \
		./print_x.c \
		./print_p.c \
		./print_percent.c \


LIBFT_DIR = ../libft
LIBFT_SRCS = $(LIBFT_DIR)/*.c

OBJS = $(SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

.PHONY : bonus all clean fclean re

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I$(LIBFT_DIR)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	mv $(LIBFT_DIR)/libft.a $(NAME)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

bonus: all

clean:
	@make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
