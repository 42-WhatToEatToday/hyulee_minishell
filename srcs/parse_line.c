/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:34:48 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/02 22:23:16 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_state *g_state;

void	remove_quotes(t_tok *tok, char **tokens)
{
	int		i;
	int		j;
	int		k;
	char		new_token[MAX_STR];
	
	i = 1;
	while (tokens[i])
	{
		j = 0;
		k = 0;
		while (tokens[i][j])
		{
			if (tokens[i][j] == '\'' && !(tok->flag & DQUOTE))
			{
				tok->flag ^= QUOTE;
				++j;
			}
			else if (tokens[i][j] == '\"' && !(tok->flag & QUOTE))
			{
				tok->flag ^= DQUOTE;
				++j;
			}
			while (!(tok->flag & QUOTE) && !(tok->flag & DQUOTE) && tokens[i][j])
			{
				new_token[k++] = tokens[i][j++];
				if (tokens[i][j] == '\'' || tokens[i][j] == '\"')
					break;
			}
			while (tok->flag & QUOTE && tokens[i][j])
			{
				if (tokens[i][j] == '\'')
				{
					tok->flag ^= QUOTE;
					++j;
					break;
				}
				new_token[k++] = tokens[i][j++];
			}
			while (tok->flag & DQUOTE && tokens[i][j])
			{
				if (tokens[i][j] == '\"')
				{
					tok->flag ^= DQUOTE;
					++j;
					break;
				}
				new_token[k++] = tokens[i][j++];
			}
		}
		new_token[k] = 0;
		free(tokens[i]);
		tokens[i] = ft_strdup(new_token);
		++i;
	}
}

void	parse_line(t_state *s, char *input)
{
	char	**cmds;
	char	**piped;
	t_cmds	*cmds_curr;
	int		i;

	if (!(cmds = split_delimiter(input, ';')))
		exit(1);
	i = 0;
	while (cmds[i])
	{
		if (!(cmds_curr = create_command(NULL)))
			exit(1);
		if (!(piped = split_delimiter(cmds[i], '|')))
			exit(1);
		if (!(piped = handle_env_var(s, piped)))
			exit(1);
		if (!(tokenize(cmds_curr, piped)))
			exit(1);
		append_command(&(s->cmds), cmds_curr);
		free_array(piped);
		i++;
	}
	free_array(cmds);
}
