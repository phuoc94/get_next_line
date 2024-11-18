/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:59:19 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/18 16:17:05 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY | O_CREAT);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);

	while (line)
	{
		printf("this is your line: %s\n", line);
		line = get_next_line(fd);

	}

	free(line);
	return (0);
}
