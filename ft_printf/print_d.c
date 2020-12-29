/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 05:27:46 by hyulee            #+#    #+#             */
/*   Updated: 2020/08/06 02:14:50 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	print_d_left_sort(t_flags *flags, char *str, int *n)
{
	putchar_n(flags->sign, n);
	while (flags->precision-- >= 1)
		putchar_n('0', n);
	ft_putstr_fd(str, 1);
	*n += ft_strlen(str);
	while (flags->width-- >= 1)
		putchar_n(' ', n);
}

static void	print_d_right_sort(t_flags *flags, char *str, int *n)
{
	while (flags->width-- >= 1)
		putchar_n(' ', n);
	putchar_n(flags->sign, n);
	while (flags->precision-- >= 1)
		putchar_n('0', n);
	ft_putstr_fd(str, 1);
	*n += ft_strlen(str);
}

static void	print_d_right_sort_zero(t_flags *flags, char *str, int *n)
{
	if (flags->dot == 1)
	{
		while (flags->width-- >= 1)
			putchar_n(' ', n);
		putchar_n(flags->sign, n);
	}
	else
	{
		putchar_n(flags->sign, n);
		while (flags->width-- >= 1)
			putchar_n('0', n);
	}
	ft_putstr_fd(str, 1);
	*n += ft_strlen(str);
}

static void	check_precision(t_flags *flags, int dec, char *str, int strlen_t)
{
	if (flags->plus == 1 && dec >= 0)
	{
		flags->sign = '+';
		strlen_t++;
	}
	else if (flags->space == 1 && dec >= 0)
	{
		flags->sign = ' ';
		strlen_t++;
	}
	if (flags->precision < 0)
		flags->dot = -1;
	if (flags->precision > (int)ft_strlen(str))
		flags->precision -= (int)ft_strlen(str);
	else
		flags->precision = 0;
	if (flags->width > strlen_t + flags->precision)
		flags->width -= (strlen_t + flags->precision);
	else
		flags->width = 0;
}

void		print_d(t_flags *flags, va_list args, int *n)
{
	int		dec;
	int		strlen_t;
	char	*str;
	char	*temp;

	dec = va_arg(args, int);
	if (flags->dot == 1 && flags->precision == 0 && dec == 0)
		str = ft_strdup("");
	else
		str = ft_itoa(dec);
	temp = str;
	strlen_t = (int)ft_strlen(str);
	if (*str == '-')
	{
		flags->sign = '-';
		str++;
	}
	check_precision(flags, dec, str, strlen_t);
	if (flags->minus == 1)
		print_d_left_sort(flags, str, n);
	else if (flags->zero == 1 && flags->precision == 0)
		print_d_right_sort_zero(flags, str, n);
	else
		print_d_right_sort(flags, str, n);
	free(temp);
}
