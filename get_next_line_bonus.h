/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knottey <Twitter:@knottey>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:20:42 by knottey           #+#    #+#             */
/*   Updated: 2023/05/26 20:20:42 by knottey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_list
{
	int				fd;
	char			*save;
	struct s_list	*next;
}	t_list;

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_len(char const *s1, char const *s2, size_t n1, size_t n2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_list	*create_newfd_elem(t_list **lst, int fd);

char	*get_next_line(int fd);

#endif