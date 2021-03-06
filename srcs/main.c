/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 01:40:53 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/12 18:59:55 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state *g_state;

static void	init(t_state *s)
{
	s->env_head = 0;
	s->input = 0;
	s->cmds = 0;
	s->curr_cmds = 0;
	s->waiting = 0;
	s->exitnum = 0;
	s->rd_fd = 0;
	s->wrt_fd = 1;
}

static int	parse_env(t_env **head, char *envp[])
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
			{
				key = ft_strndup(envp[i], j);
				value = ft_strdup(&envp[i][j + 1]);
				break ;
			}
			j++;
		}
		add_list_back(head, key, value);
		frees(key, value, 0);
	}
	return (1);
}

int			main(int argc, char *argv[], char *envp[])
{
	t_state state;
	char	**envp_head;

	(void)argc;
	(void)argv;
	init(&state);
	g_state = &state;
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, (void *)sigquit_handler);
	parse_env(&(state.env_head), envp);
	envp_head = get_envp(&(state.env_head));
	ft_strlcpy(state.home, find_env(&(state.env_head), "HOME")->value,
			MAX_PATH_LENGTH);
	prompt(&state, envp_head);
	free_array(envp_head);
	return (0);
}
