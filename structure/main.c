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

int main(int argc, char *argv[])
{
	int		fd;
	char 	*line;

	if (argc != 2)
		return (0);
	line = "";
	fd = open(argv[1], O_RDONLY);
	//(void)argc;
	//(void)argv;
	while (line)
	{
		line = get_next_line(fd);
		//printf(">>> %s", line);
		free(line);
	}
	return (0);
}