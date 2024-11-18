/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:46:51 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/18 19:18:32 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //printf

void	free_list(t_list **list)
{
	t_node	*current;
	t_node	*next;

	current = (*list)->head;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	free(*list);
	*list = NULL;
}

t_list	**create_list(t_list **list, int fd, int *line_len)
{
	char	*buffer;
	int		sz;
	t_list	**tmp;

	while (!found_newline((*list)->tail))
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(*buffer));
		if (!buffer)
			return (NULL);
		sz = read(fd, buffer, BUFFER_SIZE);
		if (sz <= 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[sz] = '\0';
		tmp = add_to_list(list, buffer, line_len);
		if (!tmp)
		{
			free_list(list);
			return (NULL);
		}
		free(buffer);
	}
	return (list);
}

t_list	**add_to_list(t_list **list, char *buffer, int *line_len)
{
	t_node	*new_node;
	char	*tmp;

	tmp = ft_strdup_delim(buffer, '\n', 1, line_len);
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
	if (!(*list)->head)
	{
		(*list)->head = new_node;
		(*list)->tail = new_node;
	}
	else
	{
		(*list)->tail->next = new_node;
		(*list)->tail = new_node;
	}
	return (list);
}

void	copy_list_to_line(t_list **list, char *line)
{
	t_node	*current;
	int		i;
	char	*content_ptr;

	i = 0;
	current = (*list)->head;
	while (current)
	{
		content_ptr = current->content;
		while (*content_ptr != '\0')
			line[i++] = *content_ptr++;
		current = current->next;
	}
	line[i] = '\0';
}

char	*get_next_line(int fd)
{
	t_list	*list;
	char	*next_line;
	int		line_len;

	if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0))
		return (NULL);
	line_len = 0;
	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	if (!create_list(&list, fd, &line_len))
		return (NULL);
	next_line = malloc((line_len + 1) * sizeof(*next_line));
	if (!next_line)
	{
		free_list(&list);
		return (NULL);
	}
	copy_list_to_line(&list, next_line);
	free_list(&list);
	return (next_line);
}
