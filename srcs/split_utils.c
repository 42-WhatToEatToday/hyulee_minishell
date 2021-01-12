/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 13:31:14 by kyoukim           #+#    #+#             */
/*   Updated: 2021/01/12 14:28:53 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	handle_redirection_in_split(char *s, int i, int *j, int *flag)
{
	if (!(*flag & REDI_IN) && !(*flag & REDI_OUT))
	{
		if (i != *j)
			return (0);
		if (s[*j] == '<')
			*flag ^= REDI_IN;
		else if (s[*j] == '>')
			*flag ^= REDI_OUT;
	}
	if (s[*j] == '>' && *flag & REDI_OUT)
	{
		if (s[*j + 1] != '>')
		{
			(*j)++;
			return (0);
		}
	}
	else if (s[*j] == '<' && *flag & REDI_IN)
	{
		(*j)++;
		return (0);
	}
	return (1);
}

static int	get_moved_index(char *s, int i, char c, int *flag)
{
	int	j;

	j = i;
	while (((*flag & QUOTE || *flag & DQUOTE)
		&& s[j] == c) || (s[j] != c && s[j]))
	{
		if (s[j] == '\'' && !(*flag & DQUOTE))
			*flag ^= QUOTE;
		else if (s[j] == '\"' && !(*flag & QUOTE))
			*flag ^= DQUOTE;
		if (!(*flag & QUOTE) && !(*flag & DQUOTE)
		&& *flag & TOKENIZE && (s[j] == '<' || s[j] == '>'))
			if (!handle_redirection_in_split(s, i, &j, flag))
				break ;
		++j;
	}
	return (j);
}

static void	toggle_redirection_flags(char *s, int *i, int *flag)
{
	if (*flag & TOKENIZE && (s[*i] == '<' || *flag & REDI_IN))
		*flag ^= REDI_IN;
	else if (*flag & TOKENIZE && (s[*i] == '>' || *flag & REDI_OUT))
		*flag ^= REDI_OUT;
	else
		(*i)++;
}

int			put_words_in_ret(char **ret, char *s, char c, int flag)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = get_moved_index(s, i, c, &flag);
			if (!(ret[k] = (char*)malloc(sizeof(char) * (j - i + 1))))
				if (destroy_ans(ret, k))
					return (0);
			ft_strlcpy(ret[k], &s[i], j - i + 1);
			k++;
			i = j;
		}
		if (s[i] != '\0')
			toggle_redirection_flags(s, &i, &flag);
	}
	ret[k] = NULL;
	return (1);
}
