/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knottey <Twitter:@knottey>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:46:23 by knottey           #+#    #+#             */
/*   Updated: 2023/05/21 13:12:29 by knottey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	ssize_t	nread;
	char	*buf;
	size_t	buf_size = 128;

	buf = (char *)malloc(sizeof(char) * buf_size);
	if (buf == NULL)
		return (NULL);
	nread = read(fd, buf, buf_size);
	if (nread <= 0)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}