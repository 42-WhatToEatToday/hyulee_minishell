/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 04:41:40 by hyulee            #+#    #+#             */
/*   Updated: 2020/07/05 00:10:40 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*temp;

	if (s == 0)
		return (0);
	else if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (!(temp = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		temp[i] = s[start + i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
