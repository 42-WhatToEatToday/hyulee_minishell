/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 22:24:36 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/05 19:00:43 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_state *g_state;

int	ft_cd(t_state *s, t_cmd cmd)
{
	char buf[MAX_PATH_LENGTH];

	if (cmd.argv[1] == NULL || ft_strcmp(cmd.argv[1], "~") == 0)
		cmd.argv[1] = find_env(&(s->env_head), "HOME")->value;
	if (chdir(cmd.argv[1]) == -1)
	{
		ft_printf("sh: %s: %s: No such file or directory\n", cmd.argv[0], cmd.argv[1]);
		s->exitnum = 22; // 일 아닌가요??
	}
	getcwd(buf, MAX_PATH_LENGTH);
	change_env(&(s->env_head), "PWD", buf);
	return (1);
}
