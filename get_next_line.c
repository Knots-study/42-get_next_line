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

static int	ft_join_line_buf(char **line, char *buf)
{
	char	*temp;
	
	temp = *line;
	*line = ft_strjoin(*line, buf);
	free(temp);
	return (1);
}

static int	ft_split_endl(char **line, char **save, char *buf)
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
	return (0);
}

static int	ft_read_until_endl(int fd, char **line, char **save)
{	
	int		read_flag;
	ssize_t	read_byte;
	char	*buf;

	read_flag = 1;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (-1);
	read_byte = 1;
	while (read_flag == 1 && read_byte > 0)
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		buf[read_byte] = '\0';
		if (ft_strchr(buf, '\n'))
		{
			read_flag = ft_split_endl(line, save, buf);
			break ;
		}
		else
			read_flag = ft_join_line_buf(line, buf);//これでbufをくっつけたlineができる
		
	}
	free(buf);
	if (read_flag == 1 && read_byte == 0)
		*line = NULL;
	return (read_flag);
}

static int	ft_join_save(char **line, char **save)
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
		return (0);
	}
	else
	{
		tmp = *line;
		*line = *save;
		*save = NULL;
		free(tmp);
		return (1);
	}
}

char	*get_next_line(int fd)
{
	int			read_flag;
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0 || !(line = ft_strdup("")))
		return (NULL);
	read_flag = 1;
	if (save)
		read_flag = ft_join_save(&line, &save);
	if (read_flag == 1)
		read_flag = ft_read_until_endl(fd, &line, &save);
	return (line);
}