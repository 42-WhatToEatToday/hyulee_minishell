/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 07:00:32 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/08 01:31:30 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_state *g_state;

static int	is_valid_identifier(char c)
{
	return ((65 <= c && c <= 90) || c == '_');
}

int	ft_unset(t_state *s, t_cmd cmd)
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
			ft_printf("bash: unset: \'%c\': not a valid identifier\n", cmd.argv[i][0]);
			s->exitnum = 1;
			break;
		}
		delete_env(&(s->env_head), cmd.argv[i]);
		i++;
	}
	s->exitnum = 0;
	return (1);
}
