/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:01:46 by kyoukim           #+#    #+#             */
/*   Updated: 2021/01/06 12:32:26 by kyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

static int	is_valid_exitnum(char *num)
{
	int	i;
	int	s;

	i = 0;
	while (num[i] && is_space(num[i]))
		++i;
	s = i;
	if (num[i] == '+' || num[i] == '-')
		++i;
	while (num[i] && is_num(num[i]))
		++i;
	while (num[i] && num[i] == ' ')
		++i;
	if (!num[i])
	{
		if (ft_atoi(num) == -1 && (num[s] != '-' || 
			(num[s + 1] != '1' || is_num(num[s + 2]))))
			return (2);
		return (0);
	}
	return (1);
}	

static void	exit_with_designated_exitnum(t_cmd cmd)
{
	int	ret;

	ret = 0;
	if ((ret = is_valid_exitnum(cmd.argv[1])))
	{
		ft_printf("in");
		ft_putstr_fd("sh: exit: ", 2);
		ft_putstr_fd(cmd.argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		if (ret == 1)
			exit(128);
		if (ret == 2)
			exit(255);
	}
	else
		exit(ft_atoi(cmd.argv[1]));
}


int	ft_exit(t_state *s, t_cmd cmd)
{
	ft_putstr_fd("exit\n", 2);
	if (cmd.argv_num == 1)
		exit(s->exitnum);
	else if (cmd.argv_num == 2)
		exit_with_designated_exitnum(cmd);
	else
	{
		s->exitnum = 1;
		ft_putstr_fd("sh: exit: too many arguments\n", 2);
	}
	return (1);
}
