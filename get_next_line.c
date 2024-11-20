/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:46:51 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/20 21:39:43 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //printf

t_list	*create_list(t_list *list, int fd)
{
	char	*buffer;
	int		sz;

	while (!found_newline(list->tail))
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(*buffer));
		if (!buffer)
			return (NULL);
		sz = read(fd, buffer, BUFFER_SIZE);
		if (sz == 0)
		{
			free(buffer);
			return (list);
		}
		buffer[sz] = '\0';
		if (!add_to_list(list, buffer))
		{
			free_list(list);
			return (NULL);
		}
		free(buffer);
	}
	return (list);
}

t_list	*add_to_list(t_list *list, char *buffer)
{
	t_node	*new_node;
	char	*tmp;

	tmp = ft_strdup_buffer(buffer);
	if (!tmp)
		return (NULL);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
	{
		free(tmp);
		return (NULL);
	}
	new_node->content = tmp;
	new_node->next = NULL;
	if (!list->head)
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		list->tail->next = new_node;
		list->tail = new_node;
	}
	return (list);
}

char 	*copy_list_to_line(t_list *list, char *next_line_head, int line_len)
{
	t_node	*current;
	int		i;
	char	*content_ptr;
	int		k;
	char	*line;

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
	return line;
}

t_list	*initialize_list(t_list *list)
{
	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;
	int				line_len;
	char			*next_line_head;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0))
		return (NULL);
	if (!list)
		list = initialize_list(list);
	if (!list)
		return (NULL);
	if (!create_list(list, fd))
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
