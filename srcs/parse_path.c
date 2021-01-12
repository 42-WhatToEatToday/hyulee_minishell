/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 23:43:54 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/12 18:52:52 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	bind_path(char *dir, char *path, char *input, int size)
{
	dir[0] = '\0';
	ft_strlcat(dir, path, size);
	ft_strlcat(dir, "/", size);
	ft_strlcat(dir, input, size);
}

int			check_path(t_state *s, t_cmd *cmd)
{
	char		**path;
	char		*dir;
	int			i;
	size_t		size;
	struct stat	sb;

	i = -1;
	path = parse_path(s);
	while (path[++i])
	{
		size = ft_strlen(path[i]) + ft_strlen("/") + ft_strlen(cmd->command);
		if (!(dir = (char *)malloc(sizeof(char) * (size + 1))))
			exit(0);
		bind_path(dir, path[i], cmd->command, size + 1);
		if (stat(dir, &sb) == 0)
		{
			cmd->command = dir;
			free_array(path);
			return (1);
		}
		frees(dir, 0, 0);
	}
	free_array(path);
	return (0);
}

char		**parse_path(t_state *s)
{
	char	*path;
	char	**ret;

	if (find_env(&(s->env_head), "PATH"))
	{
		path = find_env(&(s->env_head), "PATH")->value;
		ret = ft_split(path, ':');
	}
	else
	{
		ret = (char **)malloc(sizeof(char *));
		ret[0] = NULL;
	}
	return (ret);
}
