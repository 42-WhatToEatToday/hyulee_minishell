/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 06:20:15 by hyulee            #+#    #+#             */
/*   Updated: 2020/08/05 06:21:42 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	in_width(t_flags *flags, va_list args, char **format_ptr)
{
	if (**format_ptr == '*')
	{
		flags->width = va_arg(args, int);
		if (flags->width < 0)
		{
			flags->minus = 1;
			flags->width *= -1;
		}
		(*format_ptr)++;
	}
	else if (ft_isdigit(**format_ptr))
		flags->width = ft_atoi(*format_ptr);
	while (ft_isdigit(**format_ptr))
		(*format_ptr)++;
}

void	in_precision(t_flags *flags, va_list args, char **format_ptr)
{
	if (**format_ptr == '.')
	{
		flags->dot = 1;
		(*format_ptr)++;
		if (**format_ptr == '*')
		{
			flags->precision = va_arg(args, int);
			(*format_ptr)++;
		}
		else if (ft_isdigit(**format_ptr))
			flags->precision = ft_atoi(*format_ptr);
		while (ft_isdigit(**format_ptr))
			(*format_ptr)++;
	}
}

void	init_flags(t_flags *flags)
{
	flags->plus = 0;
	flags->minus = 0;
	flags->space = 0;
	flags->zero = 0;
	flags->dot = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->type = 0;
	flags->sign = 0;
}

int		in_flags(t_flags *flags, char format_ptr)
{
	if (format_ptr == '-')
		flags->minus = 1;
	else if (format_ptr == '+')
		flags->plus = 1;
	else if (format_ptr == ' ')
		flags->space = 1;
	else if (format_ptr == '0')
		flags->zero = 1;
	else
		return (0);
	return (1);
}
