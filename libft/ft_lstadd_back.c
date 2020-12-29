/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 00:44:27 by hyulee            #+#    #+#             */
/*   Updated: 2020/07/03 01:45:28 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *temp;

	if (lst == 0 || new == 0)
		return ;
	if (*lst == 0)
	{
		(*lst) = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
	new->next = 0;
	return ;
}
