/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyulee <hyulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 00:02:14 by hyulee            #+#    #+#             */
/*   Updated: 2021/01/06 23:36:08 by hyulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int		find_ret_value(char **line, char **backup, char *buf)
{
	char	*temp;
	char	*left_line;

	left_line = ft_strchr(*backup, '\n');
	if (buf != 0)
		free(buf);
	if (left_line != 0)
	{
		*line = ft_strndup(*backup, left_line - *backup);
		temp = ft_strndup(left_line + 1, ft_strlen(left_line + 1));
		if (*backup != 0)
			free(*backup);
		*backup = temp;
		return (SUCCESS);
	}
	if (*backup != 0)
	{
		*line = *backup;
		*backup = 0;
	}
	else
		*line = ft_strndup("", 1);
	return (ENDOFFILE);
}

char	*get_temp(char *backup, char *buf, ssize_t read_size)
{
	if (backup == 0)
		return (ft_strndup(buf, read_size));
	else
		return (ft_strjoin(backup, buf));
}

int		find_new_line(char **backup, char **buff, int fd, char **temp)
{
	ssize_t	read_size;
	char	*buf;

	buf = *buff;
	if (ft_strchr(*backup, '\n') == 0)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size > 0)
		{
			buf[read_size] = '\0';
			*temp = get_temp(*backup, buf, read_size);
			if (*backup != 0)
				free(*backup);
			*backup = *temp;
		}
		return (read_size);
	}
	else
		return (0);
}

int		get_next_line(int fd, char **line)
{
	static char *backup[MAX_FD];
	char		*buf;
	char		*temp;
	ssize_t		read_size;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ERROR);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (ERROR);
	while ((read_size = find_new_line(&backup[fd], &buf, fd, &temp)) > 0)
	{
		if (read_size < BUFFER_SIZE)
			break ;
	}
	if (read_size < 0)
	{
		free(buf);
		return (ERROR);
	}
	return (find_ret_value(line, &backup[fd], buf));
}
