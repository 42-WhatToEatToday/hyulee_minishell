/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:24:45 by hyulee            #+#    #+#             */
/*   Updated: 2020/07/05 00:14:33 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_power(int power)
{
	int	n;

	n = 1;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	while (power > 0)
	{
		n *= 10;
		--power;
	}
	return (n);
}

static int	get_count(int n)
{
	int count;

	count = 0;
	if (n < 0)
	{
		n = n / 10 * (-1);
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_itoa_pos(int n, int count, int power)
{
	char	*ret;
	int		i;

	i = 0;
	if (!(ret = (char *)malloc(sizeof(char) * (count + 1))))
		return (0);
	while (power > 0)
	{
		ret[i] = (n / power) + '0';
		i++;
		n = n % power;
		power /= 10;
	}
	ret[i] = '\0';
	return (ret);
}

static char	*ft_itoa_neg(int n, int count, int power)
{
	char	*ret;
	int		i;

	i = 1;
	if (!(ret = (char *)malloc(sizeof(char) * (count + 2))))
		return (0);
	ret[0] = '-';
	if (n < 0)
	{
		ret[i] = ((n / power) * (-1)) + '0';
		i++;
		n = (n % power) * (-1);
		power /= 10;
	}
	while (power > 0)
	{
		ret[i] = (n / power) + '0';
		i++;
		n = n % power;
		power /= 10;
	}
	ret[i] = '\0';
	return (ret);
}

char		*ft_itoa(int n)
{
	char	*result;
	int		count;
	int		power;

	count = get_count(n);
	power = get_power(count - 1);
	if (n < 0)
	{
		result = ft_itoa_neg(n, count, power);
	}
	else if (n == 0)
	{
		if (!(result = (char *)malloc(sizeof(char) * 2)))
			return (0);
		result[0] = '0';
		result[1] = '\0';
	}
	else
	{
		result = ft_itoa_pos(n, count, power);
	}
	return (result);
}
