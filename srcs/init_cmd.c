/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:23:26 by kyoukim           #+#    #+#             */
/*   Updated: 2021/01/12 15:49:29 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_new_tokens(t_state *s, char **new_tokens)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s->curr_cmds->curr_tok->tokens[i])
	{
		if (search_token(s, ">", &i) != -1 ||
				search_token(s, ">>", &i) != -1 ||
				search_token(s, "<", &i) != -1)
			free_redirection(s->curr_cmds->curr_tok->tokens, &i);
		else
		{
			new_tokens[j] =
				ft_strdup(s->curr_cmds->curr_tok->tokens[i]);
			free(s->curr_cmds->curr_tok->tokens[i]);
			s->curr_cmds->curr_tok->tokens[i] = NULL;
			++j;
		}
		++i;
	}
	new_tokens[j] = NULL;
	free(s->curr_cmds->curr_tok->tokens);
	s->curr_cmds->curr_tok->tokens = new_tokens;
}

int			init_cmd(t_state *s, t_cmd *cmd)
{
	char	**new_tokens;

	if (!(new_tokens = (char **)malloc(sizeof(char *) * MAX_STR)))
		return (0);
	create_new_tokens(s, new_tokens);
	cmd->argv = new_tokens;
	cmd->command = cmd->argv[0];
	cmd->argv_num = get_argv_num(*cmd);
	return (1);
}
