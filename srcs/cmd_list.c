/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 20:17:18 by hyulee            #+#    #+#             */
/*   Updated: 2020/12/29 20:28:04 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state *g_state;

t_cmds			*create_command(t_tok *data)
{
	t_cmds	*new_cmds;

	if (!(new_cmds = (t_cmds *)malloc(sizeof(t_cmds))))
		return (NULL);
	new_cmds->tokens = data;
	new_cmds->next = NULL;
	return (new_cmds);
}

static t_cmds	*last_command(t_cmds *cmds)
{
	if (cmds)
	{
		while (cmds->next)
			cmds = cmds->next;
	}
	return (cmds);
}

void			append_command(t_cmds **cmds, t_cmds *new)
{
	if (!cmds || !new)
		return ;
	else if (!(*cmds))
		*cmds = new;
	else
	{
		last_command(*cmds)->next = new;
		new->next = NULL;
	}
}
