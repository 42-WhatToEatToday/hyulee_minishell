/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 23:06:51 by hyulee            #+#    #+#             */
/*   Updated: 2020/07/02 23:22:23 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
	}
	else if (n > 0)
	{
		if (n / 10 != 0)
			ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + 48, fd);
	}
	else
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putnbr_fd(21474, fd);
			ft_putnbr_fd(83648, fd);
		}
		else
			ft_putnbr_fd(-n, fd);
	}
}
