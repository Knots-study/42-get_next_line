/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knottey <Twitter:@knottey>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:46:23 by knottey           #+#    #+#             */
/*   Updated: 2023/05/21 18:38:03 by knottey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save == NULL)
	{
		save = (char *)malloc(sizeof(char));
		if (save == NULL)
			return (NULL);
		save[0] = '\0';
	}
	save = ft_read_until_endl(fd, save);
	line = ft_cut_line_endl(save);
	save = ft_move_savep(save);
	return (line);
}

char	*ft_read_until_endl(int fd, char *save)
{	
	ssize_t	nread;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	nread = 1;
	while (!ft_strchr(save, '\n') && nread != 0)
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[nread] = '\0';
		save = ft_strjoin(save, buf);
	}
	free(buf);
	return (save);
}

char	*ft_cut_line_endl(char *save)
{
	char	*line_until_endl;
	size_t	idx;

	idx = 0;
	if (!save[idx])
		return (NULL);
	while (save[idx] != '\0' && save[idx] != '\n')
		idx++;
	line_until_endl = ft_substr(save, 0, idx + 1);
	line_until_endl[idx] = '\n';
	line_until_endl[idx + 1] = '\0';
	return (line_until_endl);
}


char	*ft_move_savep(char *save)
{
	char	*next_save;
	size_t	idx;
	
	idx = 0;
	while (save[idx] && save[idx] != '\n')
		idx++;
	if (save[idx] == '\0')
	{
		free(save);
		return (NULL);
	}
	next_save = ft_substr(save, idx + 1, ft_strlen(save) - idx);
	if (next_save == NULL)
		return (NULL);
	free(save);
	return (next_save);
}
