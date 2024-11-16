/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:46:51 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/16 23:03:14 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //printf

int	found_newline(t_node *node)
{
	char	*str;

	if (!node || !node->content)
		return (0);
	str = node->content;
	while (*str != '\0')
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

void	create_list(t_list **list, int fd, int *line_len)
{
	char	*buffer;
	int		sz;

	printf("create_list - Enter\n");
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
		add_to_node(list, buffer, line_len);
		printf("create_list - add_to_list\n");
		free(buffer);
	}
}

void	add_to_node(t_list **list, char *buffer, int *line_len)
{
	t_node	*new_node;

	printf("add_to_list - Enter\n");
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->content = ft_strdup_delim(buffer, '\n', 1, line_len);
	new_node->next = NULL;
	printf("add_to_list - new_node created\n");
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
		printf("print_line_chain - current->content: %s\n", current->content);
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
