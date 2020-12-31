/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 22:24:36 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/01 00:07:40 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_state *g_state;

void	ft_cd(t_state *s, t_cmd cmd)
{
	if (cmd.argv[1] == NULL || ft_strcmp(cmd.argv[1], "~") == 0)
		cmd.argv[1] = find_env(&(s->env_head), "HOME")->value;
	if (chdir(cmd.argv[1]) == -1)
		ft_printf("sh: %s: %s: No such file or directory\n", cmd.argv[0], cmd.argv[1]);
}