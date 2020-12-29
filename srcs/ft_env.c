/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 06:11:45 by hyulee            #+#    #+#             */
/*   Updated: 2020/12/29 22:34:11 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state *g_state;

void	ft_env(t_state *s)
{
	char **envp;

	envp = get_envp(&(s->env_head));
	while (*envp)
	{
		ft_printf("%s\n", *envp);
		envp++;
	}
}
