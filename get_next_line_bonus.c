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
#include "get_next_line_bonus.h"

static void	ft_read_until_endl(int fd, char **save)
{	
	size_t	save_len;
	ssize_t	read_byte;
	char	*buf;
	char	*temp;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return ;
	save_len = ft_strlen(*save);
	while (!ft_strchr(*save, '\n'))
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte <= 0)
			break ;
		buf[read_byte] = '\0';
		temp = *save;
		*save = ft_strjoin_len(*save, buf, save_len, read_byte + 1);
		free(temp);
		temp = NULL;
		save_len += read_byte;
	}
	free(buf);
}

static char	*ft_make_new_save(char **save, char *new_line_ptr)
{
	char	*line;
	char	*tmp;

	line = NULL;
	if (new_line_ptr)
	{
		tmp = line;
		line = ft_substr(*save, 0, new_line_ptr - *save + 1);
		free(tmp);
		tmp = NULL;
		tmp = *save;
		*save = ft_substr(new_line_ptr + 1, 0, ft_strlen(new_line_ptr + 1));
		free(tmp);
	}
	else
	{
		tmp = line;
		line = *save;
		*save = NULL;
		free(tmp);
	}
	return (line);
}

static char	*ft_new_save_line(char **save)
{
	char	*line;
	char	*new_line_ptr;

	if (**save == '\0')
	{
		free(*save);
		return (NULL);
	}
	new_line_ptr = ft_strchr(*save, '\n');
	line = ft_make_new_save(save, new_line_ptr);
	return (line);
}

static void	release_fdlist(t_list **head, t_list **target)
{
	t_list	**tmp;

	free((*target)->save);
	if (*head == *target)
		*head = (*target)->next;
	else
	{
		tmp = head;
		while ((*tmp)->next != *target)
			tmp = &((*tmp)->next);
		(*tmp)->next = (*target)->next;
	}
	free(*target);
}

char	*get_next_line(int fd)
{
	char			*line;
	static t_list	*head_point_fdlist;
	t_list			*point_fdlist;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	point_fdlist = head_point_fdlist;
	while (point_fdlist && point_fdlist->fd != fd)
		point_fdlist = point_fdlist->next;
	if (point_fdlist == NULL)
		point_fdlist = create_newfd_elem(&head_point_fdlist, fd);
	ft_read_until_endl(fd, &point_fdlist->save);
	if (!point_fdlist->save)
	{
		release_fdlist(&head_point_fdlist, &point_fdlist);
		return (NULL);
	}
	line = ft_new_save_line(&point_fdlist->save);
	return (line);
}
