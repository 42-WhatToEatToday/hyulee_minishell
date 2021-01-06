/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:53:53 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/06 12:01:53 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_state *g_state;

void	append_input(t_state *s, char **input)
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

int	is_quote_error(t_cmds *cmds)
{
	t_tok	*tok;

	tok = cmds->tokens;
	while (tok)
	{
		if (tok->flag != 0)
			return (1);
		tok = tok->next;
	}
	return (0);
}


void	execute(t_state *s, char **envp)
{
	s->curr_cmds = s->cmds;
	while (s->curr_cmds)
	{
		if (is_quote_error(s->curr_cmds))
		{
			ft_printf("ERROR: multi-line disabled.\n");
			s->exitnum = 1;
			s->curr_cmds = s->curr_cmds->next;
			continue;
		}
		execute_cmd(s, envp);
		s->curr_cmds = s->curr_cmds->next;
	}
	free_command(&(s->cmds));
}

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
	//	if (gnl_ret == 0 && handle_eof(s, &input, &input_flag))
	//		continue;  // these 2 lines
		append_input(s, &input);
		s->input = input;
		parse_line(s, s->input);
		execute(s, envp);
		free(input);
	}
}
