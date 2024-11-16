/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:46:51 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/17 00:00:15 by phuocngu         ###   ########.fr       */
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

void	print_line_chain(t_list *list)
{
	t_node	*current;

	printf("print_line_chain - Enter\n");
	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		printf("print_line_chain - current->content: %s", current->content);
		current = current->next;
	}
}

char	*get_next_line(int fd)
{
	t_list	*list;
	char	*next_line;
	int		line_len;

	line_len = 0;
	next_line = NULL;
	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	create_list(&list, fd, &line_len);
	print_line_chain(list);
	return (next_line);
}
