/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:05:03 by kyoukim           #+#    #+#             */
/*   Updated: 2021/01/11 13:16:08 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	call_builtin(t_state *s, t_cmd cmd, int *ret)
{
	if (s->rd_fd != STDIN_FILENO)
		dup2(s->rd_fd, STDIN_FILENO);
	if (s->wrt_fd != STDOUT_FILENO)
		dup2(s->wrt_fd, STDOUT_FILENO);
	if (ft_strcmp(cmd.command, "cd") == 0)
		*ret = ft_cd(s, cmd);
	else if (ft_strcmp(cmd.command, "echo") == 0)
		*ret = ft_echo(s, cmd);
	else if (ft_strcmp(cmd.command, "pwd") == 0)
		*ret = ft_pwd(s);
	else if (ft_strcmp(cmd.command, "env") == 0)
		*ret = ft_env(s);
	else if (ft_strcmp(cmd.command, "export") == 0)
		*ret = ft_export(s, cmd);
	else if (ft_strcmp(cmd.command, "unset") == 0)
		*ret = ft_unset(s, cmd);
	else if (ft_strcmp(cmd.command, "exit") == 0)
		*ret = ft_exit(s, cmd);
}

int	execute_builtin(t_state *s, t_cmd cmd)
{
	int ret;
	int stin;
	int stout;

	stin = dup(STDIN_FILENO);
	stout = dup(STDOUT_FILENO);
	ret = 0;
	call_builtin(s, cmd, &ret);
	dup2(stin, STDIN_FILENO);
	dup2(stout, STDOUT_FILENO);
	close(stin);
	close(stout);
	if (ret)
		return (1);
	return (NOT_A_BUILTIN);
}
