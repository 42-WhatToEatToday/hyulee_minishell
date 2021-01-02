/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 16:15:00 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/02 23:01:41 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_state *g_state;

void	delete_env(t_env **head, char *key)
{
	t_env *temp;
	t_env *target;

	temp = *head;
	if (ft_strcmp(temp->key, key) == 0)
	{
		*head = (*head)->next;
		frees(temp->key, temp->value, temp);
		return ;
	}
	while (temp->next)
	{
		if (ft_strcmp(temp->next->key, key) == 0)
		{
			target = temp->next;
			temp->next = temp->next->next;
			frees(target->key, target->value, target);
			return ;
		}
		temp = temp->next;
	}
}

t_env	*find_env(t_env **head, char *key)
{
	t_env *temp;

	temp = *head;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	change_env(t_env **head, char *key, char *value)
{
	t_env *temp;

	temp = find_env(head, key);
	if (temp == NULL)
		add_list_back(head, key, value);
	else if (temp->value == NULL)
		temp->value = ft_strdup(value);
	else
	{
		frees(temp->value, 0, 0);
		temp->value = ft_strdup(value);
	}
}

t_env	*create_new_env(char *key, char *value)
{
	t_env *temp;

	if (!(temp = malloc(sizeof(t_env))))
		exit(1);
	temp->next = 0;
	temp->key = ft_strdup(key);
	if (value == NULL)
		temp->value = NULL;
	else
		temp->value = ft_strdup(value);
	return (temp);
}

void	add_list_back(t_env **head, char *key, char *value)
{
	t_env *temp;

	if (*head == NULL)
		*head = create_new_env(key, value);
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = create_new_env(key, value);
	}
}
