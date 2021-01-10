/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 04:08:18 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/11 02:38:43 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*result;
	unsigned int	s_len;
	unsigned int	i;

	s_len = 0;
	i = 0;
	while (s[s_len])
		s_len++;
	result = (char *)malloc(sizeof(char) * (s_len + 1));
	if (result == 0)
		return (0);
	while (i < s_len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
