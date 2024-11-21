/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:46:51 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/21 19:58:58 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //printf

void	create_list(t_list **list, int fd)
{
	char	*buffer;
	int		sz;

	if (!(*list))
	{
		*list = malloc(sizeof(t_list));
		if (!(*list))
			return ;
		(*list)->head = NULL;
		(*list)->tail = NULL;
	}
	while (!found_newline((*list)->tail))
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
		add_to_list(*list, buffer);
	}
}

void	add_to_list(t_list *list, char *buffer)
{
	t_mynode	*new_node;

	new_node = malloc(sizeof(t_mynode));
	if (!new_node)
		return ;
	if (!list->tail)
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		list->tail->next = new_node;
		list->tail = new_node;
	}
	new_node->content = buffer;
	new_node->next = NULL;
}

char	*copy_list_to_line(t_list *list, char *next_line_head, int line_len)
{
	t_mynode	*current;
	int			i;
	char		*content_ptr;
	int			k;
	char		*line;

	i = 0;
	k = 0;
	line = malloc((line_len + 1) * sizeof(*line));
	if (!line)
	{
		free_list(list);
		return (NULL);
	}
	current = list->head;
	while (current)
	{
		content_ptr = current->content;
		while (*content_ptr != '\0' && *content_ptr != '\n')
			line[i++] = *content_ptr++;
		if (*content_ptr == '\n')
			line[i++] = *content_ptr++;
		while (*content_ptr)
			next_line_head[k++] = *content_ptr++;
		current = current->next;
	}
	next_line_head[k] = '\0';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list *list = NULL;
	char *next_line;
	int line_len;
	char *next_line_head;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (!list)
		return (NULL);
	line_len = count_line_len(list);
	next_line_head = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!next_line_head)
	{
		free_list(list);
		return (NULL);
	}
	next_line = copy_list_to_line(list, next_line_head, line_len);
	list = reinitialize_list(list, next_line_head);
	if (!list || !*next_line)
	{
		free_list(list);
		free(next_line);
		return (NULL);
	}
	return (next_line);
}