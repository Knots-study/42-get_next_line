/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knottey <Twitter:@knottey>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:46:23 by knottey           #+#    #+#             */
/*   Updated: 2023/05/21 17:19:55 by knottey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	//saveを初期化しないと、NULLポインタになって代入ができない、、、
	//static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = "";
	line = ft_read_until_endl(fd, line);
	//line = ft_cut_line_endl(line);
	return (line);
}

char	*ft_read_until_endl(int fd, char *line)
{	
	ssize_t	nread;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (buf == NULL)
		return (NULL);
	nread = 1;
	while (!ft_strchr(buf, '\n') && nread > 0)
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[nread] = '\0';
		line = ft_strjoin(line, buf);
		printf("read関数内 = %s\n", line);
	}
	free(buf);
	return (line);
}

char	*ft_cut_line_endl(char *line)
{
	char	*line_until_endl;
	size_t	idx;

	idx = 0;
	while (line[idx] != '\0' && line[idx] != '\n')
		idx++;
	line_until_endl = ft_substr(line, 0, idx + 1);
	line_until_endl[idx + 1] = '\0';
	return (line_until_endl);
}
