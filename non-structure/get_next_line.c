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

#include "get_next_line.h"

static void	ft_read_until_endl(int fd, char **save)
{	
	ssize_t	read_byte;
	char	*buf;
	char	*temp;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return ;
	while (!ft_strchr(*save, '\n'))
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte <= 0)
			break ;
		buf[read_byte] = '\0';
		temp = *save;
		*save = ft_strjoin(*save, buf);
		free(temp);
	}
	free(buf);
}

static char	*ft_new_save_endl(char **save, char *new_line_ptr)
{
	char	*line;
	char	*tmp;

	line = NULL;
	tmp = line;
	line = ft_substr(*save, 0, new_line_ptr - *save + 1);
	free(tmp);
	tmp = *save;
	*save = ft_substr(new_line_ptr + 1, 0, ft_strlen(new_line_ptr + 1));
	free(tmp);
	return (line);
}

static char	*ft_new_save_no_endl(char **save)
{
	char	*line;
	char	*tmp;

	line = NULL;
	tmp = line;
	line = *save;
	*save = NULL;
	free(tmp);
	return (line);
}

static char	*ft_new_save_line(char **save)
{
	char	*new_line_ptr;

	if (**save == '\0')
	{
		free(*save);
		return (NULL);
	}
	new_line_ptr = ft_strchr(*save, '\n');
	if (new_line_ptr)
		return (ft_new_save_endl(save, new_line_ptr));
	else
		return (ft_new_save_no_endl(save));
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_read_until_endl(fd, &save);
	if (!save)
		return (NULL);
	line = ft_new_save_line(&save);
	return (line);
}
