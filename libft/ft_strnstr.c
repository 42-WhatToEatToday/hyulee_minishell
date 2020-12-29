/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 23:16:32 by hyulee            #+#    #+#             */
/*   Updated: 2020/07/04 02:09:25 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	f_len;
	size_t	s_len;

	i = 0;
	j = 0;
	if (find[i] == '\0')
		return ((char *)src);
	s_len = ft_strlen(src);
	f_len = ft_strlen(find);
	if (s_len < f_len || len < f_len)
		return (0);
	while (i < len && f_len <= len - i && src[i] != '\0')
	{
		j = 0;
		while (src[i + j] != '\0' && src[i + j] == find[j])
		{
			if (find[j + 1] == '\0')
				return ((char *)src + i);
			j++;
		}
		i++;
	}
	return (0);
}
