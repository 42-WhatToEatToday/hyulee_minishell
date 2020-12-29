/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 19:20:38 by hyulee            #+#    #+#             */
/*   Updated: 2020/07/12 15:27:46 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_strs_len(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char		**failed_malloc(char **result)
{
	size_t	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

char			*get_str(char const *s, char c, size_t idx)
{
	size_t	len;
	size_t	idx_temp;
	char	*ret;

	len = 0;
	idx_temp = idx;
	while (s[idx] != c && s[idx] != '\0')
	{
		len++;
		idx++;
	}
	if ((ret = ft_substr(s, idx_temp, len)) == 0)
		return (0);
	ret[len] = '\0';
	return (ret);
}

size_t			skip_idx(char const *s, char c, size_t idx)
{
	size_t	i;

	i = 0;
	while (s[idx] == c && s[idx] != '\0')
	{
		idx++;
		i++;
	}
	return (i);
}

char			**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		idx;
	char		**result;

	if (s == 0)
		return (0);
	if (!(result = (char **)malloc(sizeof(char *) * (get_strs_len(s, c) + 1))))
		return (0);
	i = 0;
	idx = 0;
	while (s[idx] != '\0')
	{
		idx += skip_idx(s, c, idx);
		if (s[idx] != c && s[idx] != '\0')
		{
			if ((result[i] = get_str(s, c, idx)) == 0)
				return (failed_malloc(result));
			i++;
		}
		while (s[idx] != c && s[idx] != '\0')
			idx++;
	}
	result[i] = 0;
	return (result);
}
