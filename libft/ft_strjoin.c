/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 05:28:47 by hyulee            #+#    #+#             */
/*   Updated: 2020/12/23 23:15:25 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1,const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*temp;

	i = 0;
	j = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(temp = (char *)malloc(sizeof(char) * (size + 1))))
		return (0);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		temp[i + j] = s2[j];
		j++;
	}
	temp[i + j] = '\0';
	return (temp);
}
