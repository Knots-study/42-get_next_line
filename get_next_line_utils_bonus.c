/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knottey <Twitter:@knottey>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:46:28 by knottey           #+#    #+#             */
/*   Updated: 2023/05/27 03:15:39 by knottey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	if (s == NULL)
		return (length);
	while (s[length] != '\0')
		length++;
	return (length);
}

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0' && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin_len(char const *s1, char const *s2, size_t n1, size_t n2)
{
	size_t	idx;
	char	*join_word;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	join_word = (char *)malloc(sizeof(char) * (n1 + n2 + 1));
	if (join_word == NULL)
		return (NULL);
	idx = 0;
	while (idx < n1)
	{
		join_word[idx] = s1[idx];
		idx++;
	}
	while (idx - n1 < n2)
	{
		join_word[idx] = s2[idx - n1];
		idx++;
	}
	join_word[n1 + n2] = '\0';
	return (join_word);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	idx;
	size_t	s_len;
	char	*substr;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		len = 0;
	else if (s_len - start < len)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	idx = 0;
	while (idx < len)
	{
		substr[idx] = *(s + start + idx);
		idx++;
	}
	substr[len] = '\0';
	return (substr);
}

t_list	*create_newfd_elem(t_list **lst, int fd)
{
	t_list	*new;

	if (lst == NULL)
		return (NULL);
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->save = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		new->next = *lst;
		*lst = new;
	}
	return (*lst);
}
