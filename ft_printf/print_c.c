/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 01:10:37 by hyulee            #+#    #+#             */
/*   Updated: 2020/07/30 05:26:22 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	print_c_right(t_flags *flags, char str, int *n)
{
	ft_putchar_fd(str, 1);
	(*n)++;
	while (flags->width-- >= 1)
	{
		ft_putchar_fd(' ', 1);
		(*n)++;
	}
}

static void	print_c_left(t_flags *flags, char str, int *n)
{
	while (flags->width-- >= 1)
	{
		ft_putchar_fd(' ', 1);
		(*n)++;
	}
	ft_putchar_fd(str, 1);
	(*n)++;
}

void		print_c(t_flags *flags, va_list args, int *n)
{
	int str;
	int str_len;

	str = va_arg(args, int);
	str_len = 1;
	flags->width -= str_len;
	if (flags->minus == 1)
		print_c_right(flags, str, n);
	else
		print_c_left(flags, str, n);
}
