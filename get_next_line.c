/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knottey <Twitter:@knottey>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:46:23 by knottey           #+#    #+#             */
/*   Updated: 2023/05/23 18:20:53 by knottey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int 		read_flag;
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0 || !(line = ft_strdup("")))
		return (NULL);
	read_flag = ft_read_until_endl(fd, &line, &save);
	if (save)
		read_flag = ft_join_save(&line, &save);
	(void)read_flag;
	return (line);
}

int	ft_join_line_buf(char **line, char *buf)
{
	char	*temp;
	
	temp = *line;
	*line = ft_strjoin(*line, buf);
	free(temp);
	return (KEEP_READ);
}

int	ft_read_until_endl(int fd, char **line, char **save)
{	
	int 	read_flag;
	ssize_t	read_byte;
	char	*buf;

	read_flag = KEEP_READ;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (STOP_READ);
	read_byte = 1;
	while (read_flag == KEEP_READ && read_byte != 0)
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buf);
			return (END_READ);
		}
		buf[read_byte] = '\0';
		if (ft_strchr(buf, '\n'))
			read_flag = ft_split_endl(line, save, buf);
		else
			read_flag = ft_join_line_buf(line, buf);
	}
	free(buf);
	if (read_flag == KEEP_READ && read_byte == 0)
		read_flag = STOP_READ;
	return (read_flag);
}

int	ft_split_endl(char **line, char **save, char *buf)
{
	char	*old_line;
	char	*temp;
	char	*new_line_ptr;

	new_line_ptr = ft_strchr(buf, '\n');
	temp = ft_substr(buf, 0, new_line_ptr - buf);
	old_line = *line;//ここでアドレスを保存しておかないとstrjoinでfreeしていないのでメモリリークする
	*line = ft_strjoin(*line, temp);
	free(old_line);
	free(temp);
	*save = ft_substr(new_line_ptr + 1, 0, ft_strlen(new_line_ptr + 1));
	return (STOP_READ);
}

int	ft_join_save(char **line, char **save)
{
	char *tmp;
	char *new_line_ptr;

	new_line_ptr = ft_strchr(*save, '\n');
	if (new_line_ptr)
	{
		tmp = *line;
		*line = ft_substr(*save, 0, new_line_ptr - *save);
		free(tmp);
		tmp = *save;
		*save = ft_substr(new_line_ptr + 1, 0, ft_strlen(new_line_ptr + 1));
		free(tmp);
		return (STOP_READ);
	}
	else
	{
		tmp = *line;
		*line = *save;
		*save = NULL;
		free(tmp);
		return (KEEP_READ);
	}
}
