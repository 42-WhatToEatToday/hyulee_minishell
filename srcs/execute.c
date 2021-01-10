/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:04:14 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/10 19:57:17 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quote_error(t_cmds *cmds)
{
	t_tok	*tok;

	tok = cmds->tokens;
	while (tok)
	{
		if (tok->flag != 0)
			return (1);
		tok = tok->next;
	}
	return (0);
}

void	execute(t_state *s, char **envp)
{
	s->curr_cmds = s->cmds;
	while (s->curr_cmds)
	{
		if (is_quote_error(s->curr_cmds))
		{
			ft_printf("ERROR: multi-line disabled.\n");
			s->exitnum = 1;
			s->curr_cmds = s->curr_cmds->next;
			continue;
		}
		execute_cmd(s, envp);
		s->curr_cmds = s->curr_cmds->next;
	}
	free_command(&(s->cmds));
}
