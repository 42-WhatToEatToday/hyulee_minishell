/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 07:00:32 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/10 01:55:39 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state *g_state;

static int	is_valid_identifier(char c)
{
	return ((65 <= c && c <= 90) || c == '_');
}

int			get_argv_num(t_cmd cmd)
{
	int n;

	n = 0;
	while (cmd.argv[n])
		n++;
	return (n);
}

static int	print_all(t_env *env)
{
	while (env)
	{
		if (env->value == NULL)
			ft_printf("declare -x %s\n", env->key);
		else
			ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
	return (1);
}

int			ft_export(t_state *s, t_cmd cmd)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	if (cmd.argv_num == 1)
		return (print_all(s->env_head));
	while (cmd.argv[i])
	{
		seperate_key_value(cmd.argv[i], &key, &value);
		if (!is_valid_identifier(key[0]))
		{
			//ft_putstr_fd("sh: export: \'", 2);
			//ft_putstr_fd(&key[0], 2);
			//ft_putstr_fd("\': not a valid identifier\n", 2);
			ft_printf("sh: export: \'%c\': not a valid identifier\n", key[0]);
			s->exitnum = 1;
			break ;
		}
		change_env(&(s->env_head), key, value);
		frees(key, value, 0);
		i++;
	}
	s->exitnum = 0;
	return (1);
}
