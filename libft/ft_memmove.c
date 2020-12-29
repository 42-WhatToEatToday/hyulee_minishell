/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 01:00:14 by hyulee            #+#    #+#             */
/*   Updated: 2020/07/03 04:11:21 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*temp_src;
	unsigned char	*temp_dest;

	if (dest == src || n == 0)
		return (dest);
	temp_dest = (unsigned char *)dest;
	temp_src = (unsigned char *)src;
	if (dest < src)
	{
		while (n--)
			*temp_dest++ = *temp_src++;
	}
	else
	{
		temp_dest += (n - 1);
		temp_src += (n - 1);
		while (n--)
			*temp_dest-- = *temp_src--;
	}
	return (dest);
}
