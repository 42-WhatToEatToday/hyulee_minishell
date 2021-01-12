/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 06:19:10 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/12 18:51:04 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	bind_key_value(char *envp, t_env *env, int len)
{
	envp[0] = '\0';
	ft_strlcat(envp, env->key, len);
	ft_strlcat(envp, "=", len);
	ft_strlcat(envp, env->value, len);
}

static int	get_env_len(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		if (env->value)
			n++;
		env = env->next;
	}
	return (n);
}

char		**get_envp(t_env **head)
{
	int		i;
	int		len;
	t_env	*env;
	char	**envp;

	env = *head;
	i = get_env_len(env);
	if (!(envp = (char **)malloc(sizeof(char *) * (i + 1))))
		exit(1);
	envp[i] = 0;
	i = 0;
	while (env)
	{
		if (env->value)
		{
			len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
			if (!(envp[i] = (char *)malloc(sizeof(char) * len)))
				exit(1);
			bind_key_value(envp[i], env, len);
			i++;
		}
		env = env->next;
	}
	return (envp);
}
