/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:46:51 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/20 14:09:13 by phuocngu         ###   ########.fr       */
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

void	copy_list_to_line(t_list *list, char *line, char *next_line_head)
{
	t_node	*current;
	int		i;
	int		j;
	char	*content_ptr;
	int		k;

	i = 0;
	k = 0;
	current = list->head;
	while (current)
	{
		content_ptr = current->content;
		j = 0;
		while (content_ptr[j] != '\0' && content_ptr[j] != '\n')
			line[i++] = content_ptr[j++];
		if (content_ptr[j] == '\n')
			line[i++] = content_ptr[j++];
		while (content_ptr[j])
			next_line_head[k++] = content_ptr[j++];
		current = current->next;
	}
	next_line_head[k] = '\0';
	line[i] = '\0';
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

size_t count_line_len(t_list *list)
{
	size_t len;
	t_node *current;
	int i;

	len = 0;

	current = list->head;
	while (current)
	{
		i=0;
		while (current->content[i] != '\0' && current->content[i] != '\n')
		{
			len++;
			i++;
		}
		if(current->content[i] == '\n')
			len++;
		current = current->next;
	}
	return len;
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;
	int				line_len;
	char			*next_line_head;

	next_line_head = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0))
		return (NULL);
	if (!list)
		list = initialize_list(list);
	if (!list)
		return (NULL);
	if (!create_list(list, fd))
		return (NULL);
	line_len = count_line_len(list);
	next_line = malloc((line_len + 1) * sizeof(*next_line));
	next_line_head = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!next_line || !next_line_head)
	{
		free_list(list);
		return (NULL);
	}
	copy_list_to_line(list, next_line, next_line_head);
	reinitialize_list(list, next_line_head);
	return (next_line);
}
