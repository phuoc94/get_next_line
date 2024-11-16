/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:46:51 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/16 15:01:49 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //printf

int	found_newline(t_list *node)
{
	char	*str;

	str = node->content;
	while (*str != '\0')
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

void	create_list(t_list **line_chain, int fd)
{
	char	*buffer;
	int		sz;

	while (!found_newline(*line_chain))
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(*buffer));
		if (!buffer)
			return ;
		sz = read(fd, buffer, BUFFER_SIZE);
		if (!sz)
		{
			free(buffer);
			return ;
		}
		buffer[sz] = '\0';
		add_to_list(*line_chain, buffer);
	}
}

void	add_to_list(t_list *node, char *buffer)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = ft_strdup(buffer);
	new_node->next = NULL;
	node->next = new_node;
	node = new_node;
}

char	*get_next_line(int fd)
{
	t_list	**line_chain;
	char	*next_line;

	next_line = NULL;
	line_chain = malloc(sizeof(t_list *));
	if (!next_line)
		return (NULL);
	create_list(line_chain, fd);
	return (next_line);
}
