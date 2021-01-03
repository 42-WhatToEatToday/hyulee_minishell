/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 23:43:54 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/04 00:04:08 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_state	*g_state;

char	**parse_path(t_state *s)
{
	char	*path;
	char	**ret;

	path = find_env(&(s->env_head), "PATH")->value;
	ret = ft_split(path, ':');
	return (ret);
}
