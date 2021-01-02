/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 16:26:07 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/02 14:33:06 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state *g_state;

void	frees(void *s1, void *s2, void *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}

void	free_array(char **arrs)
{
	int	i;

	i = 0;
	while (arrs[i])
	{
		free(arrs[i]);
		i++;
	}
	free(arrs);
}

void	free_tok(t_tok **tok)
{
	t_tok	*next_node;

	if (!tok)
		return ;
	while (*tok)
	{
		next_node = (*tok)->next;
		if ((*tok)->tokens)
			free_array((*tok)->tokens);
		free(*tok);
		*tok = next_node;
	}
	return ;
}

void	free_command(t_cmds **cmds)
{
	t_cmds	*next_node;

	ft_printf("command free in\n");
	if (!cmds)
		return ;
	while (*cmds)
	{
		ft_printf("command free start\n");
		next_node = (*cmds)->next;
		if ((*cmds)->tokens)
		{
			ft_printf("tokens free start\n");
			free_tok(&((*cmds)->tokens));
		}
		free(*cmds);
		*cmds = next_node;
	}
	return ;
}

void	free_exit(t_state *s, int exitnum)
{
	free(s->input);
	free_command(&(s->cmds));
	exit(exitnum);
}
