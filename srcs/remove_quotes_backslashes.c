/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_backslashes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 00:19:55 by kyoukim           #+#    #+#             */
/*   Updated: 2021/01/12 15:49:19 by kyoukim          ###   ########.fr       */
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
}

static void	copy_til_qstart(t_tok *tok, char **new_token, char *tokens, int *j)
{
	while (!(tok->flag & QUOTE) && !(tok->flag & DQUOTE) && tokens[(*j)])
	{
		if (tokens[(*j)] == '\\' && !(tok->flag & BACKSLASH))
		{
			tok->flag ^= BACKSLASH;
			(*j)++;
			continue;
		}
		if (tok->flag & BACKSLASH)
			tok->flag ^= BACKSLASH;
		**new_token = tokens[(*j)++];
		(*new_token)++;
		if (tokens[(*j)] == '\'' || tokens[(*j)] == '\"')
			break ;
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
		**new_token = tokens[(*j)++];
		(*new_token)++;
	}
	while (tok->flag & DQUOTE && tokens[(*j)])
	{
		if (tokens[(*j)] == '\"')
		{
			tok->flag ^= DQUOTE;
			++(*j);
			break ;
		}
		**new_token = tokens[(*j)++];
		(*new_token)++;
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
