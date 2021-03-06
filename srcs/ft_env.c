/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 06:11:45 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/12 18:52:18 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_state *s)
{
	char **envp;
	char **envp_head;

	envp = get_envp(&(s->env_head));
	envp_head = envp;
	while (*envp)
	{
		ft_printf("%s\n", *envp);
		envp++;
	}
	free_array(envp_head);
	s->exitnum = 0;
	return (1);
}
