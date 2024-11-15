/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:46:51 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/15 22:54:57 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //printf


char *get_next_line(int fd)
{
	int line_len;
	int sz;
	char *buffer;
	line_len = 0;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(*buffer));
	if(!buffer)
		return (NULL);

	sz = read(fd, buffer, BUFFER_SIZE);
	buffer[sz] = '\0';

	while (sz)
	{
		printf("buffer: %s \n", buffer);
		sz = read(fd, buffer, BUFFER_SIZE);
	}

	return (char *)(0);
}
