/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:30:40 by kyoukim           #+#    #+#             */
/*   Updated: 2020/12/30 14:28:35 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void for_test(t_command *com)
{
	ft_printf("---------Command----------\n");
	int i = 0;
	while (com->tokenized)
	{
		ft_printf("Pipe %d\n", i);
		int j = 0;
		while (com->tokenized->tokens[j])
		{
			ft_printf("%s ", com->tokenized->tokens[j]);
			++j;
		}
		ft_printf("\n");
		com->tokenized = com->tokenized->next;
		i++;
	}
}*/

static int	execute_builtin(t_state *s, t_cmd cmd)
{
	if (ft_strcmp(cmd.command, "env") == 0)
	{
		return ((int)ft_env(s) = 1);
	}
	else if (ft_strcmp(cmd.command, "export") == 0)
	{
		return ((int)ft_export(s, cmd) = 1);
	}
	else if (ft_strcmp(cmd.command, "unset") == 0)
	{
		return ((int)ft_unset(s, cmd) = 1);
	}
	return NOT_A_BUILTIN;
}

int	execute_pipe(t_state *s, int read, int write, char **envp)
{
	t_cmd	cmd;
	pid_t	pid;

	cmd.command = s->curr_cmds->tokens->tokens[0];
	cmd.argv = s->curr_cmds->tokens->tokens;

	if (execute_builtin(s, cmd))
		return (SUCCESS);
	if ((pid = fork()) < 0)
		exit(0);
	if (pid == 0)
	{
		if (read != STDIN_FILENO)
		{
			dup2(read, STDIN_FILENO);
			close(read);
		}
		if (write != STDOUT_FILENO)
		{
			dup2(write, STDOUT_FILENO);
			close(write);
		}
		if (execve(s->curr_cmds->tokens->tokens[0], s->curr_cmds->tokens->tokens, envp) < 0)
			exit(0); // error message needed
	}
	else
		wait(NULL);
	return (SUCCESS);
}

int	execute(t_state *s, char **envp)
{
	pid_t	ret;
	int	read;
	int	pipefd[2];

	ret = 0;
	read = STDIN_FILENO;
	while (s->curr_cmds->tokens)
	{
		if (pipe(pipefd) < 0)
			exit(0);
		if (i == tok_size - 1)
			ret = execute_pipe(s, read, STDOUT_FILENO, envp);
		else
			ret = execute_pipe(s, read, pipefd[WRITE_END], envp);
		if (ret == ERROR)
			exit(0);
		close(pipefd[WRITE_END]);
		read = pipefd[READ_END];
		s->curr_cmds->tokens = s->curr_cmds->tokens->next;
	}
	return (1);
}
