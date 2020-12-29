/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 01:27:54 by hyulee            #+#    #+#             */
/*   Updated: 2020/07/04 02:11:52 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *temp;

	if (lst == 0)
		return ;
	temp = *lst;
	while ((*lst) != 0)
	{
		(*lst) = (*lst)->next;
		del(temp->content);
		free(temp);
		temp = *lst;
	}
	*lst = 0;
}
