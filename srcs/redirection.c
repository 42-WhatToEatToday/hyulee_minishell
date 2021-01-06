/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 01:49:09 by kyoukim           #+#    #+#             */
/*   Updated: 2021/01/07 00:48:08 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_no_file_error(t_state *s, char *arg)
{
	ft_putstr_fd("sh: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	s->exitnum = 1;
	return (0);
}

int	execute_redirection(t_state *s, char *c, int *rd, int *wrt)
{
	char	**argv;
	int	fd;
	int	index;

	argv = s->curr_cmds->curr_tok->tokens;
	if (c[0] == '<')
	{
		index = search_token(s, "<");
		if ((fd = open(argv[index + 1], O_RDONLY)) == -1)
			return (print_no_file_error(s, argv[index + 1]));
		*rd = fd;
		argv[index] = NULL;
	}
	else if (c[0] == '>')
	{
		if (c[1] == '>' && c[2] == '\0')
		{
			index = search_token(s, ">>");
			fd = open(argv[index + 1], O_CREAT|O_APPEND|O_WRONLY, 0644);
		}
		else if (c[1] == '\0')
		{
			index = search_token(s, ">");
			fd = open(argv[index + 1], O_CREAT|O_TRUNC|O_WRONLY, 0644);
		}
		*wrt = fd;
	}
	return (1);
}

int	search_token(t_state *s, char *c)
{
	int	i;

	i = 0;
	while (s->curr_cmds->curr_tok->tokens[i])
	{
		if (!ft_strcmp(s->curr_cmds->curr_tok->tokens[i], c))
			return (i);
		++i;
	}
	return (0);
}
