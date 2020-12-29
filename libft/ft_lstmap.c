/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 01:52:17 by hyulee            #+#    #+#             */
/*   Updated: 2020/07/03 02:23:35 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	**result;

	if (lst == 0 || f == 0)
		return (0);
	result = (t_list **)ft_calloc(ft_lstsize(lst), sizeof(t_list));
	while (lst != 0)
	{
		if (!(temp = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(result, del);
			return (0);
		}
		ft_lstadd_back(result, temp);
		lst = lst->next;
		temp = temp->next;
	}
	return (*result);
}
