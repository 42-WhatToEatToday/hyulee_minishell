/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:38:12 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/10 18:16:36 by kyoukim          ###   ########.fr       */
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
	new_tok->flag = 0;
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
		if (!(curr = create_tok(NULL)))
			return (0);
		if (!(tokens = split_delimiter(piped[i], ' ')))
			return (0);
		remove_quotes(curr, tokens);
		curr->tokens = tokens;
		append_tok(&(cmds->tokens), curr);
		i++;
	}
	return (1);
}
