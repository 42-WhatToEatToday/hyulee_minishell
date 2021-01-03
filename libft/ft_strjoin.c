/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 05:28:47 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/04 01:50:03 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1,const char *s2)
{
	size_t	size;
	char	*temp;
	
	if (s1 == 0 && s2 == 0)
		return (ft_strdup(""));
	if (s1 == 0 || s2 == 0)
	{
		if (s1 == 0)
			return (ft_strdup(s2));
		return (ft_strdup(s1));
	}
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(temp = (char *)malloc(sizeof(char) * (size + 1))))
		return (0);
	ft_memcpy(temp, s1, ft_strlen(s1));
	ft_memcpy(temp + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (temp);
}
