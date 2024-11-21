/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:46:41 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/21 19:59:08 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_mynode *node)
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

void	free_list(t_list *list)
{
	t_mynode	*current;
	t_mynode	*next;

	current = list->head;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	free(list);
	list = NULL;
}

size_t	count_line_len(t_list *list)
{
	size_t		len;
	t_mynode	*current;
	int			i;

	len = 0;
	current = list->head;
	while (current)
	{
		i = 0;
		while (current->content[i] != '\0' && current->content[i] != '\n')
		{
			len++;
			i++;
		}
		if (current->content[i] == '\n')
			len++;
		current = current->next;
	}
	return (len);
}

t_list	*reinitialize_list(t_list *list, char *next_line_head)
{
	t_mynode	*current;

	free_list(list);
	list = NULL;
	current = malloc(sizeof(t_mynode));
	if (!current)
	{
		free(next_line_head);
		return (NULL);
	}
	current->content = next_line_head;
	current->next = NULL;
	list = malloc(sizeof(t_list));
	if (!list)
	{
		free(next_line_head);
		free(current);
		return (NULL);
	}
	list->head = current;
	list->tail = current;
	return (list);
}
