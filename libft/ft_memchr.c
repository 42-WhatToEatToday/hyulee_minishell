/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:15:19 by hyulee            #+#    #+#             */
/*   Updated: 2020/06/30 16:14:22 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	find;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	find = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == find)
			return (str + i);
		i++;
	}
	return (0);
}
