/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 05:28:47 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/02 22:44:57 by kyoukim          ###   ########.fr       */
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

static char	*get_value(t_env **head, char *key)
{
	t_env	*env;
	char	*value;

	env = find_env(head, key);
	value = ft_strdup(env->value);
	return (value);
}

static void	free_all(char **new_piped, char *value, char *piped)
{
	free_array(new_piped);
	free(value);
	free(piped);
}

static char	**change_env_var(t_state *s, char **piped, int i, int j)
{
	int	start;
	char	**new_piped;
	int	len;
	char	*value;
	char	*joined;

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
	value = get_value(&(s->env_head), new_piped[1]);
	joined = join_strings(new_piped[0], value, new_piped[2]);
	free_all(new_piped, value, piped[i]);
	piped[i] = joined;
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
