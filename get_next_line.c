/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:46:51 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/22 11:55:17 by phuocngu         ###   ########.fr       */
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

char	*process_node(t_mynode *current, t_line_data *line_data, int *i, int *k)
{
	char	*content_ptr;

	content_ptr = current->content;
	while (*content_ptr != '\0' && *content_ptr != '\n')
		line_data->current_line[(*i)++] = *content_ptr++;
	if (*content_ptr == '\n')
		line_data->current_line[(*i)++] = *content_ptr++;
	while (*content_ptr)
		line_data->next_line[(*k)++] = *content_ptr++;
	return (line_data->current_line);
}

char	*copy_list_to_line(t_list *list, char *next_line_head)
{
	t_mynode	*current;
	int			i;
	int			k;
	char		*line;
	t_line_data	line_data;

	i = 0;
	k = 0;
	line_data.current_line_len = count_line_len(list);
	line = malloc((line_data.current_line_len + 1) * sizeof(*line));
	if (!line)
		return (NULL);
	current = list->head;
	line_data.current_line = line;
	line_data.next_line = next_line_head;
	while (current)
	{
		process_node(current, &line_data, &i, &k);
		current = current->next;
	}
	next_line_head[k] = '\0';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;
	char			*next_line_head;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line_head = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!next_line_head)
	{
		free_list(list);
		return (NULL);
	}
	next_line = copy_list_to_line(list, next_line_head);
	list = reinitialize_list(list, next_line_head);
	if (!list || !*next_line)
	{
		free_list(list);
		free(next_line);
		return (NULL);
	}
	return (next_line);
}
