/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 01:49:09 by kyoukim           #+#    #+#             */
/*   Updated: 2021/01/12 01:24:15 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(t_state *s, char *arg, int error_type)
{
	if (error_type == SYNTAX_ERROR)
	{
		ft_putstr_fd("sh: syntax error near ", 2);
		ft_putstr_fd("unexpected token `newline'\n", 2);
		s->exitnum = 2;
	}
	else if (error_type == NOFILE_ERROR)
	{
		ft_putstr_fd("sh: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		s->exitnum = 1;
	}
	return (0);
}

static int	set_fd(t_state *s, char *c, int i)
{
	char	**argv;
	int		fd;

	fd = 0;
	argv = s->curr_cmds->curr_tok->tokens;
	if (argv[i + 1] == NULL)
		return (print_error(s, NULL, SYNTAX_ERROR));
	if (c[0] == '<')
	{
		if ((fd = open(argv[i + 1], O_RDONLY)) == -1)
			return (print_error(s, argv[i + 1], NOFILE_ERROR));
		s->rd_fd = fd;
	}
	else if (c[0] == '>')
	{
		if (c[1] == '>' && c[2] == '\0')
			fd = open(argv[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
		else if (c[1] == '\0')
			fd = open(argv[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		s->wrt_fd = fd;
	}
	return (1);
}

int			search_token(t_state *s, char *c, int *i)
{
	if (!ft_strcmp(s->curr_cmds->curr_tok->tokens[*i], c))
		return (*i);
	return (0);
}

int			set_redirection(t_state *s)
{
	int		i;

	i = 0;
	while (s->curr_cmds->curr_tok->tokens[i])
	{
		if (search_token(s, ">", &i))
			if (!set_fd(s, ">", i))
				return (0);
		if (search_token(s, ">>", &i))
			if (!set_fd(s, ">>", i))
				return (0);
		if (search_token(s, "<", &i))
			if (!set_fd(s, "<", i))
				return (0);
		++i;
	}
	return (1);
}
