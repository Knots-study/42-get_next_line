/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knottey <Twitter:@knottey>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:53:10 by knottey           #+#    #+#             */
/*   Updated: 2023/05/25 19:31:42 by knottey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char 	*line;

	line = "";
	fd = open("sample1.txt", O_RDONLY);
	while (line)
	{
		line = get_next_line(fd);
		printf(">>> %s", line);
		free(line);
	}
	return (0);
}