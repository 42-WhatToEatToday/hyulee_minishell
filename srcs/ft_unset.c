/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 07:00:32 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/10 01:56:21 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern		t_state *g_state;

static int	is_valid_identifier(char c)
{
	return ((65 <= c && c <= 90) || c == '_');
}

int			ft_unset(t_state *s, t_cmd cmd)
{
	int	i;

	i = 1;
	while (cmd.argv[i])
	{
		if (!is_valid_identifier(cmd.argv[i][0]))
		{
			//ft_putstr_fd("sh: unset: \'", 2);
			//ft_putstr_fd(&cmd.argv[i][0], 2);
			//ft_putstr_fd("\': not a valid identifier\n", 2);
			ft_printf("sh: unset: \'%c\'", cmd.argv[i][0]);
			ft_printf(": not a valid identifier\n");
			s->exitnum = 1;
			break ;
		}
		delete_env(&(s->env_head), cmd.argv[i]);
		i++;
	}
	s->exitnum = 0;
	return (1);
}
