/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:16:16 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/03 00:03:14 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_state	*g_state;

void	ft_echo(t_state *s, t_cmd cmd)
{
	int	i;

	i = 1;
	s->flag = 0;
	if (ft_strcmp(cmd.argv[i], "-n") == 0)
	{
		s->flag = 1;
		i++;
	}
	while (cmd.argv[i])
	{
		ft_printf("%s", cmd.argv[i]);
		if (cmd.argv_num - 1 == i && s->flag == 1)
			;
		else if (cmd.argv_num - 1 == i)
			ft_printf("\n");
		else
			ft_printf(" ");
		i++;
	}
}