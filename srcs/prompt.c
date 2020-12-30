/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:53:53 by hyulee            #+#    #+#             */
/*   Updated: 2020/12/30 14:24:03 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_state *g_state;

void	append_input(t_state *s, char **input)
{
	char	*temp;
	
	if (!(temp = ft_strjoin(s->input, *input)))
		exit(1);
	frees(s->input, *input, 0);
	s->input = temp;
}

int		handle_eof(t_state *s, char **input, int *input_flag)
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

/*
static void	print_cmds(t_state *s)
{
	int i = 0;
	while (s->cmds)
	{
		ft_printf("-----------------------------cmd-----------------------\n");
		while (s->cmds->tokens)
		{
			i = 0;
			ft_printf("---------------------pipe-----------------------\n");
			while (s->cmds->tokens->tokens[i])
			{
				ft_printf("token : %s\n", s->cmds->tokens->tokens[i]);
				i++;
			}
			s->cmds->tokens = s->cmds->tokens->next;
		}
		s->cmds = s->cmds->next;
	}
}*/

void	prompt(t_state *s, char **envp)
{
	char	*input;
	int		gnl_ret;
	int		input_flag;
	
	input_flag = 0;
	s->input = 0;
	while (1)
	{
		if (input_flag == 0)
			write(1, "sh> ", 4);
		else if (input_flag == 1)
			write(1, ">", 1);
		input_flag = 0;
		gnl_ret = get_next_line(0, &input);
		s->input = input;
		parse_line(s, s->input);
		if (ft_strcmp(s->input, "exit") == 0)
			exit(1);
		s->curr_cmds = s->cmds;
		while (s->curr_cmds)
		{
			execute(s, envp);
			s->curr_cmds = s->curr_cmds->next;
		}
		free_command(s->cmds);
	}
}
