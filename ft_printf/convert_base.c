/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 21:29:24 by hyulee            #+#    #+#             */
/*   Updated: 2020/12/30 18:00:16 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	get_power(int power, int base_num)
{
	unsigned int	n;

	n = 1;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	while (power > 0)
	{
		n *= base_num;
		--power;
	}
	return (n);
}

static int	get_count(unsigned int n, int base_num)
{
	int count;

	count = 0;
	while (n > 0)
	{
		n /= base_num;
		count++;
	}
	return (count);
}

static char	*ft_base_to_a(unsigned int n, int count, int power, char *base)
{
	char	*ret;
	int		i;
	int		base_num;

	i = 0;
	base_num = ft_strlen(base);
	if (!(ret = (char *)malloc(sizeof(char) * (count + 1))))
		return (0);
	while (power > 0)
	{
		ret[i] = base[n / power];
		i++;
		n = n % power;
		power /= base_num;
	}
	ret[i] = '\0';
	return (ret);
}

char		*convert_base(unsigned int n, char *base)
{
	char	*result;
	int		count;
	int		power;
	int		base_num;

	base_num = ft_strlen(base);
	count = get_count(n, base_num);
	power = get_power(count - 1, base_num);
	if (n == 0)
	{
		if (!(result = (char *)malloc(sizeof(char) * 2)))
			return (0);
		result[0] = '0';
		result[1] = '\0';
	}
	else
		result = ft_base_to_a(n, count, power, base);
	return (result);
}
