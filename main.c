/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knottey <Twitter:@knottey>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:53:10 by knottey           #+#    #+#             */
/*   Updated: 2023/05/25 00:07:14 by knottey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char 	*line;

	line = "";
	fd = open("sample.txt", O_RDONLY);
	while (line)
	{
		line = get_next_line(fd);
		printf(">>> %s\n", line);
		free(line);
	}
	return (0);
}