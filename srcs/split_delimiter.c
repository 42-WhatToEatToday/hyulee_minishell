/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:57:09 by kyoukim           #+#    #+#             */
/*   Updated: 2021/01/10 19:59:17 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**split_delimiter(char *s, char c)
{
	char	**ret;
	int		flag;

	if (!s)
		return (NULL);
	flag = 0;
	if (c == ' ')
		flag ^= TOKENIZE;
	if (!(ret = (char **)malloc(sizeof(char *) * MAX_COM)))
		return (NULL);
	if (!(put_words_in_ret(ret, s, c, flag)))
		return (NULL);
	return (ret);
}
