/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:00:45 by hyulee            #+#    #+#             */
/*   Updated: 2020/12/29 15:30:37 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state *g_state;

void sigint_handler(int signo)
{
	(void)signo;
	ft_printf("\b\b  \nsh> ");
}

void sigquit_handler(int signo)
{
	(void)signo;
	ft_printf("\b\b  \b\b");
	ft_printf("sigquit\n");
}
