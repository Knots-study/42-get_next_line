/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knottey <Twitter:@knottey>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:46:23 by knottey           #+#    #+#             */
/*   Updated: 2023/05/22 19:45:24 by knottey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save == NULL)
		save = ft_strdup("");
	save = ft_read_until_endl(fd, save);
	line = ft_cut_line_endl(&save);
	return (line);
}

char	*ft_read_until_endl(int fd, char *save)
{	
	ssize_t	nread;
	char	*buf;
	char	*new_save;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	nread = 1;
	while (!ft_strchr(save, '\n') && nread > 0)
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[nread] = '\0';
		new_save = ft_strjoin(save, buf);
		free(save);
		printf("%p\n",save);
		save = new_save;
	}
	free(buf);
	return (save);
}

char	*ft_cut_line_endl(char **save)
{
    char *line_until_endl;
    size_t idx;

    idx = 0;
    if (save == NULL || *save == NULL || *save[idx] == '\0')
        return (NULL);
    while ((*save)[idx] != '\0' && (*save)[idx] != '\n')
	{
        idx++;
	}
	line_until_endl = (char *)malloc(sizeof(char) * (idx + 2));
    if (line_until_endl == NULL)
		return (NULL);
	ft_memcpy(line_until_endl, *save, idx);
    line_until_endl[idx] = '\n';
    line_until_endl[idx + 1] = '\0';
    *save += idx + 1;
    return (line_until_endl);
}
