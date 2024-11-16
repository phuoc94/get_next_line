/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:46:51 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/16 18:42:12 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //printf

int	found_newline(t_list *node)
{
	char	*str;

	str = node->content;
	if (!str)
		return (0);
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
		add_to_list(line_chain, buffer);
		line_chain = &(*line_chain)->next;
		free(buffer);
	}
}

void	add_to_list(t_list **line_chain, char *buffer)
{
	t_list	*new_node;
	t_list	*temp;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = ft_strdup_delim(buffer, '\n', 1);
	new_node->next = NULL;
	if (*line_chain == NULL)
		*line_chain = new_node;
	else
	{
		temp = *line_chain;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	print_line_chain(t_list *line_chain)
{
	t_list	*current;

	current = line_chain;
	while (current != NULL)
	{
		printf("%s", current->content);
		current = current->next;
	}
}

char	*get_next_line(int fd)
{
	t_list	*line_chain;
	char	*next_line;

	next_line = NULL;
	line_chain = malloc(sizeof(t_list));
	if (!line_chain)
		return (NULL);
	line_chain->content = NULL;
	line_chain->next = NULL;
	printf("Calling create_list\n");
	create_list(&line_chain, fd);
	printf("Printing line_chain\n");
	print_line_chain(line_chain);
	return (next_line);
}
