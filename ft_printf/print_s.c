/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 03:57:09 by hyulee            #+#    #+#             */
/*   Updated: 2020/08/04 02:56:46 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	print_s_left_sort(t_flags *flags, char *str, int *n)
{
	if (flags->dot == 1)
	{
		while (flags->precision-- >= 1)
		{
			putchar_n(*str, n);
			str++;
		}
	}
	else
	{
		ft_putstr_fd(str, 1);
		*n += ft_strlen(str);
	}
	while (flags->width-- >= 1)
		putchar_n(' ', n);
}

static void	print_s_right_sort(t_flags *flags, char *str, int *n)
{
	while (flags->width-- >= 1)
		putchar_n(' ', n);
	if (flags->dot == 1)
	{
		while (flags->precision-- >= 1)
		{
			putchar_n(*str, n);
			str++;
		}
	}
	else
	{
		ft_putstr_fd(str, 1);
		*n += ft_strlen(str);
	}
}

void		print_s(t_flags *flags, va_list args, int *n)
{
	int		str_len;
	char	*str;

	str = va_arg(args, char *);
	if (str == NULL)
		str = "(null)";
	str_len = ft_strlen(str);
	if (flags->precision > str_len)
		flags->precision = str_len;
	else if (flags->precision < 0)
	{
		flags->dot = 0;
		flags->precision = 0;
	}
	if (flags->dot == 1 && flags->precision >= 0)
		flags->width -= flags->precision;
	else
		flags->width -= str_len;
	if (flags->minus == 1)
		print_s_left_sort(flags, str, n);
	else
		print_s_right_sort(flags, str, n);
}
