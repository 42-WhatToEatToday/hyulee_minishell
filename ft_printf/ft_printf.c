/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 04:18:10 by hyulee            #+#    #+#             */
/*   Updated: 2020/08/05 06:34:56 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		ft_printf(const char *format, ...)
{
	va_list		args;
	int			printed_char;

	printed_char = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			handle_percent((char **)&format, args, &printed_char);
		else if (*format != '%')
		{
			ft_putchar_fd(*format, 1);
			printed_char++;
			format++;
		}
	}
	va_end(args);
	return (printed_char);
}

void	handle_percent(char **format, va_list args, int *n)
{
	char	*format_ptr;
	t_flags	*flags;

	format_ptr = ++(*format);
	flags = malloc(sizeof(t_flags));
	init_flags(flags);
	while (in_flags(flags, *format_ptr))
		format_ptr++;
	in_width(flags, args, &format_ptr);
	in_precision(flags, args, &format_ptr);
	if (check_type(*format_ptr))
		flags->type = *format_ptr++;
	print_type(flags, args, n);
	*format = format_ptr;
	free(flags);
}

void	print_type(t_flags *flags, va_list args, int *n)
{
	if (flags->type == 'c')
		print_c(flags, args, n);
	else if (flags->type == 's')
		print_s(flags, args, n);
	else if (flags->type == 'd' || flags->type == 'i')
		print_d(flags, args, n);
	else if (flags->type == 'p')
		print_p(flags, args, n);
	else if (flags->type == 'u')
		print_u(flags, args, n);
	else if (flags->type == 'x' || flags->type == 'X')
		print_x(flags, args, n);
	else if (flags->type == '%')
		print_percent(flags, n);
}

int		check_type(char format_ptr)
{
	char *all_types;

	all_types = "sSpdDioOuUxXcC%";
	while (*all_types)
	{
		if (format_ptr == *all_types)
			return (1);
		all_types++;
	}
	return (0);
}
