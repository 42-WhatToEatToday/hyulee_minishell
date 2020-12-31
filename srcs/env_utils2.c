/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 16:23:17 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/01 01:49:25 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_state *g_state;

void	seperate_key_value(char *argv, char **key, char **value)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '=')
			break;
		i++;
	}
	if (ft_strlen(argv) == i)
	{
		*key = ft_strndup(argv, i);
		*value = NULL;
	}
	else
	{
		*key = ft_strndup(argv, i);
		*value = ft_strdup(&argv[i + 1]);
	}
}
