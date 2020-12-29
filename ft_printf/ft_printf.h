/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 04:15:17 by hyulee            #+#    #+#             */
/*   Updated: 2020/08/05 06:16:49 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>

# define HEX_UPPER	"0123456789ABCDEF"
# define HEX_LOWER	"0123456789abcdef"
# define OCT		"01234567"

typedef struct	s_flags
{
	int			plus;
	int			minus;
	int			space;
	int			zero;
	int			dot;
	int			width;
	int			precision;
	char		type;
	char		sign;
}				t_flags;

int				ft_printf(const char *format, ...);
void			handle_percent(char **format, va_list args, int *n);
void			init_flags(t_flags *flags);
int				in_flags(t_flags *flags, char format_ptr);
void			in_width(t_flags *flags, va_list args, char **format_ptr);
void			in_precision(t_flags *flags, va_list args, char **format_ptr);
void			print_type(t_flags *flags, va_list args, int *n);
int				check_type(char format_ptr);
void			putchar_n(char c, int *n);
char			*convert_base(unsigned int n, char *base);
char			*convert_address(unsigned long long n, char *base);
void			print_c(t_flags *flags, va_list args, int *n);
void			print_s(t_flags *flags, va_list args, int *n);
void			print_d(t_flags *flags, va_list args, int *n);
void			print_u(t_flags *flags, va_list args, int *n);
void			print_x(t_flags *flags, va_list args, int *n);
void			print_p(t_flags *flags, va_list args, int *n);
void			print_percent(t_flags *flags, int *n);

#endif
