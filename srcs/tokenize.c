/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:38:12 by hyulee            #+#    #+#             */
/*   Updated: 2020/12/29 21:04:39 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state *g_state;

int				get_tok_size(t_tok *tok)
{
	int	n;

	n = 0;
	while (tok)
	{
		tok = tok->next;
		n++;
	}
	return (n);
}

t_tok			*create_tok(char **data)
{
	t_tok	*new_tok;

	if (!(new_tok = (t_tok *)malloc(sizeof(t_tok))))
		return (NULL);
	new_tok->tokens = data;
	new_tok->next = NULL;
	return (new_tok);
}

static t_tok	*last_tok(t_tok *tok)
{
	if (tok)
	{
		while (tok->next)
			tok = tok->next;
	}
	return (tok);
}

void			append_tok(t_tok **tok, t_tok *new)
{
	if (!tok || !new)
		return ;
	else if (!(*tok))
		*tok = new;
	else
	{
		last_tok(*tok)->next = new;
		new->next = NULL;
	}
}

int				tokenize(t_cmds *cmds, char **piped)
{
	char	**tokens;
	t_tok	*curr;
	int		i;

	i = 0;
	while (piped[i])
	{
		if (!(tokens = split_delimiter(piped[i], ' ')))
			return (0);
//		remove_quotes(tokens);
		if (!(curr = create_tok(tokens)))
			return (0);
		append_tok(&(cmds->tokens), curr);
		i++;
	}
	return (1);
}
