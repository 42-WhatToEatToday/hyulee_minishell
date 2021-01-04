/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 23:41:26 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/05 05:13:33 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_state *g_state;

int	ft_pwd(t_state *s)
{
	char	buf[MAX_PATH_LENGTH];

	getcwd(buf, MAX_PATH_LENGTH);
	change_env(&(s->env_head), "PWD", buf);
	ft_printf("%s\n", buf);
	return (1);
}
