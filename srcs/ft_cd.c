/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 22:24:36 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/12 18:57:16 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(t_state *s, t_cmd cmd, int error_type)
{
	ft_putstr_fd("sh: cd: ", 2);
	ft_putstr_fd(cmd.argv[1], 2);
	if (error_type == NOFILE_ERROR)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (error_type == NOTDIR_ERROR)
		ft_putstr_fd(": Not a directory\n", 2);
	s->exitnum = 1;
	return (1);
}

int		ft_cd(t_state *s, t_cmd cmd)
{
	char	buf[MAX_PATH_LENGTH];
	DIR	*dp;

	if (cmd.argv[1] == NULL || ft_strcmp(cmd.argv[1], "~") == 0)
	{
		frees(cmd.argv[1], 0, 0);
		cmd.argv[1] = ft_strdup(s->home);
		cmd.argv[2] = NULL;
	}
	if ((dp = opendir(cmd.argv[1])) == NULL)
	{
		closedir(dp);
		return (print_error(s, cmd, NOTDIR_ERROR));
	}
	closedir(dp);
	if (chdir(cmd.argv[1]) == -1)
		return (print_error(s, cmd, NOFILE_ERROR));
	getcwd(buf, MAX_PATH_LENGTH);
	change_env(&(s->env_head), "PWD", buf);
	s->exitnum = 0;
	return (1);
}
