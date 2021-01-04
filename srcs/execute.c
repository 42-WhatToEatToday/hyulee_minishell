/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:30:40 by kyoukim           #+#    #+#             */
/*   Updated: 2021/01/05 05:22:23 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_builtin(t_state *s, t_cmd cmd)
{
	int ret;
	int stin;
	int stout;

	stin = dup(STDIN_FILENO);
	stout = dup(STDOUT_FILENO);
	if (rd != STDIN_FILENO)
		dup2(rd, STDIN_FILENO);
	if (wrt != STDOUT_FILENO)
		dup2(wrt, STDOUT_FILENO);
	ret = 0;
	if (ft_strcmp(cmd.command, "cd") == 0)
		ret = ft_cd(s, cmd);
	else if (ft_strcmp(cmd.command, "echo") == 0)
		ret = ft_echo(s, cmd);
	else if (ft_strcmp(cmd.command, "pwd") == 0)
		ret = ft_pwd(s);
	else if (ft_strcmp(cmd.command, "env") == 0)
		ret = ft_env(s);
	else if (ft_strcmp(cmd.command, "export") == 0)
		ret = ft_export(s, cmd);
	else if (ft_strcmp(cmd.command, "unset") == 0)
		ret = ft_unset(s, cmd);
	else if (ft_strcmp(cmd.command, "exit") == 0)
		ret = ft_exit(s, cmd);
	dup2(stin, STDIN_FILENO);
	dup2(stout, STDOUT_FILENO);
	close(stin);
	close(stout);
	if (ret)
		return (1);
	return (NOT_A_BUILTIN);
}

static	init_cmd(t_cmd *cmd, t_state *s)
{
	cmd->command = s->curr_cmds->curr_tok->tokens[0];
	cmd->argv = s->curr_cmds->curr_tok->tokens;
	cmd->argv_num = get_argv_num(*cmd);
}

void	execute_pipe(t_state *s, int rd, int wrt, char **envp)
{
	t_cmd	cmd;
	pid_t	pid;

	init_cmd(&cmd, s);
	if (execute_builtin(s, cmd, rd, wrt))
		return ;
	if ((pid = fork()) < 0)
		exit(1);
	if (pid == 0)
	{
		if (rd != STDIN_FILENO)
		{
			dup2(rd, STDIN_FILENO);
			close(rd);
		}
		if (wrt != STDOUT_FILENO)
		{
			dup2(wrt, STDOUT_FILENO);
			close(wrt);
		}
		if (execve(cmd.command, cmd.argv, envp) < 0)
			exit(1); // error message needed
	}
	else
		wait(NULL);
}

int	execute_cmd(t_state *s, char **envp)
{
	int	tok_size;
	int	rd;
	int	pipefd[2];

	rd = STDIN_FILENO;
	tok_size = get_tok_size(s->curr_cmds->tokens);
	s->curr_cmds->curr_tok = s->curr_cmds->tokens;
	while (tok_size--)
	{
		if (pipe(pipefd) < 0)
			exit(1);
		if (tok_size == 0)
			execute_pipe(s, rd, STDOUT_FILENO, envp);
		else
			execute_pipe(s, rd, pipefd[WRITE_END], envp);
		close(pipefd[WRITE_END]);
		if (rd != STDIN_FILENO)
			close(rd);
		rd = pipefd[READ_END];
		s->curr_cmds->curr_tok = s->curr_cmds->curr_tok->next;
	}
	return (1);
}
