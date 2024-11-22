/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:59:19 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/22 11:21:26 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("file.txt", O_RDONLY | O_CREAT);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	i = 1;
	while (line)
	{
		printf("line %d: %s\n", i++, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}
