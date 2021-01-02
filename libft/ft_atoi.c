/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 01:17:39 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/02 15:50:55 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_limits(const char *str, int i, int sign)
{
	int		cnt;
	int		idx;
	char	*l_max;
	char	*l_min;

	l_max = "9223372036854775807";
	l_min = "9223372036854775808";
	cnt = 0;
	idx = i;
	while ('0' <= str[idx] && str[idx] <= '9')
	{
		idx++;
		cnt++;
	}
	if (sign == 1 && cnt > 19)
		return (1);
	else if (sign == -1 && cnt > 19)
		return (-1);
	else if (sign == 1 && cnt == 19 && ft_strncmp(&str[i], l_max, cnt) > 0)
		return (1);
	else if (sign == -1 && cnt == 19 && ft_strncmp(&str[i], l_min, cnt) > 0)
		return (-1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	int i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (check_limits(str, i, sign) == 1)
		return (-1);
	else if (check_limits(str, i, sign) == -1)
		return (-1);
	while ('0' <= str[i] && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
