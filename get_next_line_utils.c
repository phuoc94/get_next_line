/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:46:41 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/19 19:45:13 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strdup_delim(const char *s, char delimiter, int *line_len)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	ptr = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		if (s[i] != delimiter)
			len++;
		i++;
	}
	if (s[len] == delimiter)
		len++;
	ptr[i] = '\0';
	*line_len += len;
	return (ptr);
}

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

void	reinitialize_list(t_list **list, char *next_line_head)
{
	t_node	*current;

	free_list(list);
	*list = malloc(sizeof(t_list));
	current = malloc(sizeof(t_node));
	current->content = next_line_head;
	current->next = NULL;
	(*list)->head = current;
	(*list)->tail = current;
}
