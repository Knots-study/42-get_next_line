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

// static void	ft_join_line_buf(char **save, char *buf)
// {
// 	char *temp;

// 	temp = *save;
// 	*save = ft_strjoin(*save, buf);
// 	free(temp);
// }

// static void	ft_split_endl(char **line, char **save, char *buf)
// {
// 	char	*old_line;
// 	char	*temp;
// 	char	*new_line_ptr;

// 	new_line_ptr = ft_strchr(buf, '\n');
// 	if (new_line_ptr)
// 	{
// 		temp = ft_substr(buf, 0, new_line_ptr - buf);
// 		old_line = *line;
// 		*line = ft_strjoin(*line, temp);
// 		free(old_line);
// 		free(temp);
// 		*save = ft_substr(new_line_ptr + 1, 0, ft_strlen(new_line_ptr + 1));
// 	}
// 	else
// 		*save = NULL;
// }

static void	ft_read_until_endl(int fd, char **save)
{	
	ssize_t	rb;
	char	*buf;
	char	*temp;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return ;
	rb = 1;
	while (!ft_strchr(*save, '\n') && (rb = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[rb] = '\0';	
		temp = *save;
		*save = ft_strjoin(*save, buf);
		free(temp);
	}
	free(buf);
}

static char	*ft_join_save(char **save)
{
	char *line;
	char *tmp;
	char *new_line_ptr;

	line = NULL;
	new_line_ptr = ft_strchr(*save, '\n');
	//saveの中に改行がある場合、line(出力するもの)を新たに生成。saveを動かす
	if (new_line_ptr)
	{
		tmp = line;
		line = ft_substr(*save, 0, new_line_ptr - *save);
		free(tmp);
		tmp = *save;
		*save = ft_substr(new_line_ptr + 1, 0, ft_strlen(new_line_ptr + 1));
		free(tmp);
		return (line);
	}
	else
	//saveの中に改行がない場合、line(出力するもの)を新たに生成(完成版じゃない)。saveをNULLにする
	{
		tmp = line;
		line = *save;
		*save = NULL;
		free(tmp);
		return (line);
	}
}

// saveがNULLの時にNULLを返すようにする必要がある
char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_read_until_endl(fd, &save);
	if (!save)
		return (NULL);
	line = ft_join_save(&save);
	return (line);
}