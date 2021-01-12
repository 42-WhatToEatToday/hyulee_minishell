/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_backslashes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 00:19:55 by kyoukim           #+#    #+#             */
/*   Updated: 2021/01/12 19:02:57 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	toggle_flag(t_tok *tok, char c, int *j)
{
	if (c == '\'' && !(tok->flag & DQUOTE))
	{
		tok->flag ^= QUOTE;
		(*j)++;
	}
	else if (c == '\"' && !(tok->flag & QUOTE))
	{
		tok->flag ^= DQUOTE;
		(*j)++;
	}
	else if (c == '\\' && !(tok->flag & BACKSLASH))
	{
		tok->flag ^= BACKSLASH;
		(*j)++;
	}
}

static void	copy_til_qstart(t_tok *tok, char **new_token, char *tokens, int *j)
{
	while (!(tok->flag & QUOTE) && !(tok->flag & DQUOTE) && tokens[(*j)])
	{
		if (tokens[(*j)] == '\'' || tokens[(*j)] == '\"' ||
				(tokens[(*j)] == '\\' && !(tok->flag & BACKSLASH)))
			break ;
		if (tok->flag & BACKSLASH)
			tok->flag ^= BACKSLASH;
		**new_token = tokens[(*j)++];
		(*new_token)++;
	}
}

static void	copy_til_qend(t_tok *tok, char **new_token, char *tokens, int *j)
{
	while (tok->flag & QUOTE && tokens[(*j)])
	{
		if (tokens[(*j)] == '\'')
		{
			tok->flag ^= QUOTE;
			++(*j);
			break ;
		}
		*(*new_token)++ = tokens[(*j)++];
	}
	while (tok->flag & DQUOTE && tokens[(*j)])
	{
		if (tokens[(*j)] == '\"')
		{
			tok->flag ^= DQUOTE;
			++(*j);
			break ;
		}
		if (tokens[(*j)] == '\\' && tokens[(*j) + 1] == '\\'
				&& !(tok->flag & BACKSLASH))
			break ;
		*(*new_token)++ = tokens[(*j)++];
		if (tok->flag & BACKSLASH)
			tok->flag ^= BACKSLASH;
	}
}

static void	create_new_token(t_tok *tok, char *tokens, char *new_token)
{
	int	j;

	j = 0;
	while (tokens[j])
	{
		toggle_flag(tok, tokens[j], &j);
		copy_til_qstart(tok, &new_token, tokens, &j);
		copy_til_qend(tok, &new_token, tokens, &j);
	}
	*new_token = 0;
}

void		remove_quotes_backslashes(t_tok *tok, char **tokens)
{
	int		i;
	char	new_token[MAX_STR];

	i = 0;
	while (tokens[i])
	{
		create_new_token(tok, tokens[i], new_token);
		free(tokens[i]);
		tokens[i] = ft_strdup(new_token);
		++i;
	}
	tok->flag = 0;
}
