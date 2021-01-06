/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 23:43:54 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/07 02:29:40 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_state	*g_state;

static void	bind_path(char *dir, char *path, char *input, int size)
{
		dir[0] = '\0';
		ft_strlcat(dir, path, size);
		ft_strlcat(dir, "/", size);
		ft_strlcat(dir, input, size);
}

int		check_path(t_state *s, t_cmd *cmd)
{
	char	**path;
	char	*dir;
	size_t	size;
	struct stat	sb;

	path = parse_path(s);
	while (*path)
	{
		size = ft_strlen(*path) + ft_strlen("/") + ft_strlen(cmd->command) + 1;
		if (!(dir = (char *)malloc(sizeof(char) * (size))))
			exit(0);
		bind_path(dir, *path, cmd->command, size);
		if (stat(dir, &sb) == 0)
		{
			cmd->command = dir;
			return (1);
		}
		frees(dir, 0, 0);
		path++;
	}
	return (0);
}

char	**parse_path(t_state *s)
{
	char	*path;
	char	**ret;

	path = find_env(&(s->env_head), "PATH")->value;
	ret = ft_split(path, ':');
	return (ret);
}
