/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 07:00:32 by hyulee            #+#    #+#             */
/*   Updated: 2020/12/29 13:52:53 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state *g_state;

static void	print_all(t_env *env)
{
	while(env)
	{
		if (env->value == NULL)
			ft_printf("declare -x %s\n", env->key);
		else
			ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

void		ft_export(t_state *s, t_cmd cmd)
{
	int		i;
	char	*key;
	char	*value;
	
	i = 1;
	if (cmd.argv_num == 1)
		return(print_all(s->env_head));
	while (cmd.argv[i])
	{
		seperate_key_value(cmd.argv[i], &key, &value);
		change_env(&(s->env_head), key, value);
		frees(key, value, 0);
		i++;
	}
}
