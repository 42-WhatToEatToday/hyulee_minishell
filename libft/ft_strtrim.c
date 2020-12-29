/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 06:07:47 by hyulee            #+#    #+#             */
/*   Updated: 2020/07/03 03:51:37 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_start(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (s1[i] != '\0' && set[j] != '\0')
	{
		j = 0;
		flag = 0;
		while (set[j] != '\0' && s1[i + 1] != '\0')
		{
			if (s1[i] == set[j])
			{
				i++;
				flag = 1;
				break ;
			}
			j++;
		}
		if (flag == 0)
			break ;
	}
	return (i);
}

static int	find_end(char const *s1, char const *set)
{
	int	i;
	int	j;
	int flag;

	i = ft_strlen(s1) - 1;
	j = 0;
	flag = 0;
	while (i >= 0 && set[j] != '\0')
	{
		j = 0;
		flag = 0;
		while (set[j] != '\0' && i >= 0)
		{
			if (s1[i] == set[j])
			{
				i--;
				flag = 1;
				break ;
			}
			j++;
		}
		if (flag == 0)
			break ;
	}
	return (i);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*temp;
	int		i;
	int		len;
	int		start_i;
	int		end_i;

	i = 0;
	if (s1 == 0)
		return (0);
	start_i = find_start(s1, set);
	end_i = find_end(s1, set);
	len = end_i - start_i + 1;
	if (start_i > end_i)
		return (ft_strdup(""));
	if (!(temp = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len)
	{
		temp[i] = s1[start_i];
		i++;
		start_i++;
	}
	temp[i] = '\0';
	return (temp);
}
