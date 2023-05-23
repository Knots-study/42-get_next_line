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
	int 		read_byte;
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0 || !(line = ft_strdup("")))
		return (NULL);
	read_byte = 1;
	if (save)
		read_byte = join_save(&line, &save);
	line = ft_read_until_endl(fd, read_byte, &line, &save);
	if (!save)
		return (NULL);
	return (line);
}

char	*ft_read_until_endl(int fd, int read_flag, char **line, char **save)
{	
	ssize_t	readbyte;
	char	*buf;
	char	*new_save;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	readbyte = 1;
	while (read_flag == 1 && (readbyte = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[readbyte] = '\0';
		if (ft_strchr(buf, '\n'))
			read_flag = ft_split_endl(line, save, buf);
		else{
			new_save = *line;
			*line = ft_strjoin(*line, buf);
			free(new_save);
		}
	}
	free(buf);
	return (*line);
}

int	ft_split_endl(char **line, char **save, char *buf)
{
	char	*old_line;
	char	*tmp;
	char	*new_line_ptr;

	new_line_ptr = ft_strchr(buf, '\n');
	tmp = ft_substr(buf, 0, new_line_ptr - buf);
	old_line = *line;//ここでアドレスを保存しておかないとstrjoinでfreeしていないのでメモリリークする
	*line = ft_strjoin(*line, tmp);
	free(old_line);
	free(tmp);
	*save = ft_substr(new_line_ptr + 1, 0, ft_strlen(new_line_ptr + 1));
	return (0);
}

int	join_save(char **line, char **save)
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
