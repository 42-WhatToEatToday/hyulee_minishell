# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/21 14:46:02 by hyulee            #+#    #+#              #
#    Updated: 2021/01/08 00:08:55 by hyulee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -g3 -fsanitize=address -g -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs 
RM = rm -f

SRCS =	./srcs/main.c \
		./srcs/cmd_list.c \
		./srcs/env_utils.c \
		./srcs/env_utils2.c \
		./srcs/envp.c \
		./srcs/execute.c \
		./srcs/execute_utils.c \
		./srcs/handle_env_var.c \
		./srcs/signal.c \
		./srcs/prompt.c \
		./srcs/parse_line.c \
		./srcs/parse_path.c \
		./srcs/redirection.c \
		./srcs/remove_quotes.c \
		./srcs/split_delimiter.c \
		./srcs/split_utils.c \
		./srcs/ft_echo.c \
		./srcs/ft_cd.c \
		./srcs/ft_pwd.c \
		./srcs/ft_env.c \
		./srcs/ft_export.c \
		./srcs/ft_unset.c \
		./srcs/ft_exit.c \
		./srcs/tokenize.c \
		./srcs/free_utils.c 

INCS = -I libft -I ft_printf -I includes

PRINTF_DIR = ./ft_printf
LPRINTF = $(PRINTF_DIR)/libftprintf.a

OBJS = $(SRCS:.c=.o)

.PHONY : bonus all clean fclean re

all: $(NAME)

$(NAME):
	@make -C ft_printf/
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LPRINTF) $(INCS)

bonus: all

clean:
	@make clean -C $(PRINTF_DIR)
	$(RM) $(OBJS)

fclean: clean
	rm -rf $(LPRINTF)
	$(RM) $(NAME)

re: fclean all
