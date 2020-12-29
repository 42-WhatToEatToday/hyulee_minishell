/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 20:32:07 by hyulee            #+#    #+#             */
/*   Updated: 2020/06/30 20:42:05 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	find;
	char	*temp;
	size_t	i;

	find = (char)c;
	temp = (char *)s;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (temp[i] == find)
			return (temp + i);
		i--;
	}
	if (temp[i] == find)
		return (temp);
	return (0);
}
