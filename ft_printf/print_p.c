/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:58:56 by hyulee            #+#    #+#             */
/*   Updated: 2020/08/06 03:09:15 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	print_p_left_sort(t_flags *flags, char *str, int *n)
{
	putchar_n(flags->sign, n);
	while (flags->precision-- >= 1)
		putchar_n('0', n);
	ft_putstr_fd(str, 1);
	*n += ft_strlen(str);
	while (flags->width-- >= 1)
		putchar_n(' ', n);
}

static void	print_p_right_sort(t_flags *flags, char *str, int *n)
{
	while (flags->width-- >= 1)
		putchar_n(' ', n);
	putchar_n(flags->sign, n);
	while (flags->precision-- >= 1)
		putchar_n('0', n);
	ft_putstr_fd(str, 1);
	*n += ft_strlen(str);
}

static void	print_p_right_sort_zero(t_flags *flags, char *str, int *n)
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

static void	check_precision(t_flags *flags, char *str, int strlen_t)
{
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

void		print_p(t_flags *flags, va_list args, int *n)
{
	unsigned long long	address;
	unsigned int		strlen_t;
	char				*str;
	char				*temp;

	address = va_arg(args, unsigned long long);
	if (flags->dot == 1 && flags->precision == 0
		&& address == (unsigned long long)NULL)
		temp = ft_strdup("");
	else
		temp = convert_address(address, HEX_LOWER);
	str = ft_strjoin("0x", temp);
	strlen_t = ft_strlen(str);
	check_precision(flags, str, strlen_t);
	if (flags->minus == 1)
		print_p_left_sort(flags, str, n);
	else if (flags->zero == 1 && flags->precision == 0)
		print_p_right_sort_zero(flags, str, n);
	else
		print_p_right_sort(flags, str, n);
	free(temp);
	free(str);
}
