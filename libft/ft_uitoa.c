/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:24:45 by hyulee            #+#    #+#             */
/*   Updated: 2020/12/30 18:03:42 by kyoukim          ###   ########.fr       */
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

static int	get_count(unsigned int n)
{
	int count;

	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_uitoa_pos(unsigned int n, int count, int power)
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

char		*ft_uitoa(unsigned int n)
{
	char	*result;
	int		count;
	int		power;

	count = get_count(n);
	power = get_power(count - 1);
	if (n == 0)
	{
		if (!(result = (char *)malloc(sizeof(char) * 2)))
			return (0);
		result[0] = '0';
		result[1] = '\0';
	}
	else
		result = ft_uitoa_pos(n, count, power);
	return (result);
}
