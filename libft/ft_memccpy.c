/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 00:18:32 by hyulee            #+#    #+#             */
/*   Updated: 2020/06/30 03:04:41 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*temp_dest;
	unsigned char	*temp_src;
	unsigned char	find;
	size_t			i;

	i = 0;
	temp_src = (unsigned char *)src;
	temp_dest = (unsigned char *)dest;
	find = (unsigned char)c;
	while (i < n)
	{
		temp_dest[i] = temp_src[i];
		if (temp_src[i] == find)
			return (dest + (i + 1));
		i++;
	}
	return (0);
}
