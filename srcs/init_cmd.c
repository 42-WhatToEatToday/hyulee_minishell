/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:48:20 by kyoukim           #+#    #+#             */
/*   Updated: 2021/01/10 20:51:56 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_after_index(char **argv, int index)
{
	int	i;

	i = index;
	while (argv[index])
	{
		free(argv[index]);
		index++;
	}
	argv[i] = NULL;
}

void		init_cmd(t_cmd *cmd, t_state *s)
{
	int	i;

	cmd->command = s->curr_cmds->curr_tok->tokens[0];
	i = 0;
	while (s->curr_cmds->curr_tok->tokens[i])
	{
		if (search_token(s, ">", &i) || search_token(s, ">>", &i)
				|| search_token(s, "<", &i))
		{
			free_after_index(s->curr_cmds->curr_tok->tokens, i);
			s->curr_cmds->curr_tok->tokens[i] = NULL;
			break ;
		}
		++i;
	}
	cmd->argv = s->curr_cmds->curr_tok->tokens;
	cmd->argv_num = get_argv_num(*cmd);
}
