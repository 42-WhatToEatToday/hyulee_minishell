/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:00:45 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/07 00:40:18 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state *g_state;

void sigint_handler(int signo)
{
	(void)signo;
	if (g_state->waiting == 0)
	{
		frees(g_state->input, 0, 0);
		g_state->input = 0;
		free_command(&(g_state->cmds)); 
		ft_printf("\b\b  \nsh> ");
	}
	else
		ft_printf("\b\b");
}

void sigquit_handler(int signo)
{
	(void)signo;
	ft_printf("\b\b  \b\b");
	if (g_state->waiting == 1)
		ft_printf("\b\b^\\Quit: 3\n");
}
