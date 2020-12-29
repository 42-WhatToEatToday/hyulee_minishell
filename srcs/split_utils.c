/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 13:31:14 by kyoukim           #+#    #+#             */
/*   Updated: 2020/12/29 21:00:40 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char const *s, char c)
{
	int word_count;
	int flag;

	flag = 0;
	word_count = 0;
	while (*s)
	{
		if (*s == '\"' && !(flag & DQUOTE))
			flag ^= QUOTE;
		else if (*s == '\'' && !(flag & QUOTE))
			flag ^= DQUOTE;
		if (!(flag & QUOTE) && !(flag & DQUOTE))
		{
			if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
				++word_count;
		}
		s++;
	}
	return (word_count);
}

static int	destroy_ans(char **ans, int ans_i)
{
	int i;

	i = 0;
	while (i < ans_i)
	{
		free(ans[i]);
		i++;
	}
	free(ans);
	return (1);
}

static int	put_words_in_ans(char **ans, char *s, char c)
{
	int i;
	int j;
	int ans_i;
	int flag;

	flag = 0;
	i = 0;
	ans_i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = i;
			while (((flag & QUOTE || flag & DQUOTE) && s[j] == c)
					|| (s[j] != c && s[j]))
			{
				if (s[j] == '\"' && !(flag & DQUOTE))
					flag ^= QUOTE;
				else if (s[j] == '\'' && !(flag & QUOTE))
					flag ^= DQUOTE;
				++j;
			}
			if (!(ans[ans_i] = (char*)malloc(sizeof(char) * (j - i + 1))))
				if (destroy_ans(ans, ans_i))
					return (0);
			ft_strlcpy(ans[ans_i], &s[i], j - i + 1);
			ans_i++;
			i = j;
		}
		if (s[i] != '\0')
			++i;
	}
	return (1);
}

char		**split_delimiter(char *s, char c)
{
	char	**ans;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	if (!(ans = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	ans[words] = 0;
	if (!(put_words_in_ans(ans, s, c)))
		return (NULL);
	return (ans);
}
