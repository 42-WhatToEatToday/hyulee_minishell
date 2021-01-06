/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 05:28:47 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/05 06:02:10 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_strings(const char *s1, const char *s2, const char *s3)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	size;
	char	*temp;

	i = -1;
	j = -1;
	k = -1;
	if (s1 == 0 || s2 == 0 || s3 == 0)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (!(temp = (char *)malloc(sizeof(char) * (size + 1))))
		return (0);
	while (++i < ft_strlen(s1))
		temp[i] = s1[i];
	while (++j < ft_strlen(s2))
		temp[i + j] = s2[j];
	while (++k < ft_strlen(s3))
		temp[i + j + k] = s3[k];
	temp[i + j + k] = '\0';
	return (temp);
}

static char	*get_value(t_state *s, t_env **head, char *key)
{
	t_env	*env;
	char	*value;

	if (key[0] == '\?' && key[1] == '\0')
		return (ft_itoa(s->exitnum));
	env = find_env(head, key);
	if (env)	
		value = ft_strdup(env->value);
	else
		value = NULL;
	return (value);
}

static char	**get_new_piped(char **new_piped, char **piped, int i, int j)
{
	int	start;
	int	len;

	if (!(new_piped = (char **)malloc(sizeof(char *) * 4)))
		return (NULL);
	start = j;
	while ((piped[i][j] != ' ') && (piped[i][j] != '\0'))
		++j;
	len = j - start - 1;
	new_piped[0] = ft_strndup(piped[i], start);
	new_piped[2] = ft_strdup(&piped[i][j]);
	new_piped[3] = NULL;
	if (!(new_piped[1] = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	new_piped[1][len] = '\0';
	while (len--)
		new_piped[1][len] = piped[i][--j];
	return (new_piped);
}

static char	**change_env_var(t_state *s, char **piped, int i, int j)
{
	char	**new_piped;
	char	*value;
	char	*joined;

	new_piped = NULL;
	new_piped = get_new_piped(new_piped, piped, i, j);
	value = get_value(s, &(s->env_head), new_piped[1]);
	if (value)
	{
		joined = join_strings(new_piped[0], value, new_piped[2]);
		free(piped[i]);
		piped[i] = joined;
		free(value);
	}
	free_array(new_piped);
	return (piped);
}

char	**handle_env_var(t_state *s, char **piped)
{
	int	i;
	int	j;

	i = 0;
	while (piped[i])
	{
		j = 0;
		while (piped[i][j])
		{
			if (piped[i][j] == '$')
			{
				if (!(piped = change_env_var(s, piped, i, j)))
					exit(1);
			}
			++j;
		}
		++i;
	}
	return (piped);
}
