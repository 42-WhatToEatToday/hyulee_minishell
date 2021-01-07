/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:53:53 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/08 00:11:40 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_state *g_state;

void		append_input(t_state *s, char **input)
{
	char	*temp;
	
	if (!(temp = ft_strjoin(s->input, *input)))
	{
		ft_printf("%s\n", temp);
		exit(1);
	}
	frees(s->input, *input, 0);
	s->input = temp;
}

int			handle_eof(t_state *s, char **input, int *input_flag)
{
	*input_flag = 2;
	if (ft_strlen(*input) == 0 && ft_strlen(s->input) == 0)
	{
		ft_printf("  \b\bexit\n");
		exit(0);
	}
	else
	{
		ft_printf("  \b\b");
		append_input(s, input);
	}
	return (1);
}

static int	check_escape_end(t_state *s, char **input, int *input_flag)
{
	int		i;
	char	*temp;

	i = 0;
	if ((*input)[i] == '\\')
	{
		*input_flag = 1;
		frees(*input, 0, 0);
		return (1);
	}
	else
		i = ft_strlen(*input) - 1;
	if (i >= 0 && (*input)[i] == '\\')
	{
		*input_flag = 1;
		if (i > 0)
			temp = ft_strndup(*input, i);
		append_input(s, &temp);
		frees(*input, 0, 0);
		return (1);
	}
	return (0);
}

void	for_test(t_cmds *cmds)
{
	while (cmds)
	{
		ft_printf("----------------command--------------------\n");
		int i = 0;
		while (cmds->tokens)
		{
			ft_printf("---Piped %d---\n", i);
			int j = 0;
			while (cmds->tokens->tokens[j])
			{
				ft_printf("%s$\n", cmds->tokens->tokens[j]);
				++j;
			}
			cmds->tokens = cmds->tokens->next;
			++i;
		}
		cmds = cmds->next;
	}
}

void		prompt(t_state *s, char **envp)
{
	char	*input;
	int		gnl_ret;
	int		input_flag;
	
	input_flag = 0;
	while (1)
	{
		if (input_flag == 0)
			write(1, "sh> ", 4);
		else if (input_flag == 1)
			write(1, ">", 1);
		input_flag = 0;
		gnl_ret = get_next_line(0, &input);
		if (gnl_ret == 0 && handle_eof(s, &input, &input_flag))
			continue;
		if (check_escape_end(s, &input, &input_flag))
			continue;
		append_input(s, &input);
		parse_line(s, s->input);
		//for_test(s->cmds);
		execute(s, envp);
		frees(s->input, 0, 0);
		s->input = 0;
	}
}
