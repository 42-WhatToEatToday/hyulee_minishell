/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:30:40 by kyoukim           #+#    #+#             */
/*   Updated: 2021/01/10 18:11:13 by kyoukim          ###   ########.fr       */
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
	if (s->rd_fd != STDIN_FILENO)
		dup2(s->rd_fd, STDIN_FILENO);
	if (s->wrt_fd != STDOUT_FILENO)
		dup2(s->wrt_fd, STDOUT_FILENO);
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

void			free_after_index(char **argv, int index)
{
	int	i;

	i = index;
	while (argv[index])
	{
		free(argv[index]);
		index++;
	}
	argv[i] = NULL;
}

static void	init_cmd(t_cmd *cmd, t_state *s)
{
	int	i;

	cmd->command = s->curr_cmds->curr_tok->tokens[0];
	i = 0;
	while (s->curr_cmds->curr_tok->tokens[i])
	{
		if (search_token(s, ">", &i) || search_token(s, ">>", &i) 
				|| search_token(s, "<", &i))
		{
			free_after_index(s->curr_cmds->curr_tok->tokens, i);
			s->curr_cmds->curr_tok->tokens[i] = NULL;
			break;
		}
		++i;
	}
	cmd->argv = s->curr_cmds->curr_tok->tokens;
	cmd->argv_num = get_argv_num(*cmd);
}

static void	execute_error(t_cmd cmd)
{
	ft_putstr_fd("sh: ", 2);
	ft_putstr_fd(cmd.command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	if (errno == 13)
		exit(126);
	else if (errno == 2)
		exit(127);
	exit(1);
}

void			execute_pipe(t_state *s, int wrt, char **envp)
{
	t_cmd	cmd;
	pid_t	pid;
	int		wstatus;
	int		i;

	s->wrt_fd = wrt;
	i = 0;
	while (s->curr_cmds->curr_tok->tokens[i])
	{
		if (search_token(s, ">", &i))
			execute_redirection(s, ">", i);
		if (search_token(s, ">>", &i))
			execute_redirection(s, ">>", i);
		if (search_token(s, "<", &i))
			if (!execute_redirection(s, "<", i))
				return ;
		++i;
	}
	init_cmd(&cmd, s);
	if (execute_builtin(s, cmd))
		return ;
	check_path(s, &cmd);
	if ((pid = fork()) < 0)
		exit(1);
	if (pid == 0)
	{
		if (s->rd_fd != STDIN_FILENO)
			dup2(s->rd_fd, STDIN_FILENO);
		if (s->wrt_fd != STDOUT_FILENO)
			dup2(s->wrt_fd, STDOUT_FILENO);
		if (execve(cmd.command, cmd.argv, envp) < 0)
			execute_error(cmd);
		frees(cmd.command, 0, 0);
	}
	else
	{
		s->waiting = 1;
		wait(&wstatus);
		s->waiting = 0;
		if (WIFEXITED(wstatus))
			s->exitnum = WEXITSTATUS(wstatus);
	}
}

int			execute_cmd(t_state *s, char **envp)
{
	int	tok_size;
	int	pipefd[2];

	s->rd_fd = STDIN_FILENO;
	tok_size = get_tok_size(s->curr_cmds->tokens);
	s->curr_cmds->curr_tok = s->curr_cmds->tokens;
	while (tok_size--)
	{
		if (pipe(pipefd) < 0)
			exit(1);
		if (!tok_size)
			execute_pipe(s, STDOUT_FILENO, envp);
		else
			execute_pipe(s, pipefd[WRITE_END], envp);
		close(pipefd[WRITE_END]);
		if (s->rd_fd != STDIN_FILENO)
			close(s->rd_fd);
		s->rd_fd = pipefd[READ_END];
		s->curr_cmds->curr_tok = s->curr_cmds->curr_tok->next;
	}
	return (1);
}