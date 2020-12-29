/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 18:34:59 by hyulee            #+#    #+#             */
/*   Updated: 2020/06/30 03:05:15 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *src, int c, size_t n)
{
	unsigned char	*temp;
	unsigned char	constant;
	size_t			i;

	temp = (unsigned char *)src;
	constant = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		temp[i] = constant;
		i++;
	}
	return (src);
}
