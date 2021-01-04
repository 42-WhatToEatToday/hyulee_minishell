/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:34:48 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/05 00:40:21 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_state *g_state;

void	parse_line(t_state *s, char *input)
{
	char	**cmds;
	char	**piped;
	t_cmds	*cmds_curr;
	int		i;

	if (!(cmds = split_delimiter(input, ';')))
		exit(1);
	i = 0;
	while (cmds[i])
	{
		if (!(cmds_curr = create_command(NULL)))
			exit(1);
		if (!(piped = split_delimiter(cmds[i], '|')))
			exit(1);
		if (!(piped = handle_env_var(s, piped)))
			exit(1);
		if (!(tokenize(cmds_curr, piped)))
			exit(1);
		append_command(&(s->cmds), cmds_curr);
		free_array(piped);
		i++;
	}
	free_array(cmds);
}
