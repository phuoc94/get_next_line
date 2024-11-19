/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:59:19 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/19 17:11:25 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
		if(s[len] != delimiter)
			len++;
		i++;
	}
	if(s[len] == delimiter)
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


void	polish(t_list **list, char *next_line_head)
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

	tmp = ft_strdup_delim(buffer, '\n', line_len);
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

void	copy_list_to_line(t_list **list, char *line, char *next_line_head)
{
	t_node	*current;
	int		i;
	int		j;
	char	*content_ptr;
	int		k;

	i = 0;
	k = 0;

	current = (*list)->head;
	while (current)
	{
		content_ptr = current->content;
		j = 0;
		while (content_ptr[j] != '\0' && content_ptr[j] != '\n')
			line[i++] = content_ptr[j++];
		if(content_ptr[j] == '\n')
			line[i++] = content_ptr[j++];
		while (content_ptr[j])
			next_line_head[k++] = content_ptr[j++];
		current = current->next;
	}
	next_line_head[k] = '\0';
	line[i] = '\0';
}

char	*get_next_line(int fd)
{
	static	t_list	*list = NULL;
	char			*next_line;
	int				line_len;
	char			*next_line_head;

	next_line_head = NULL;
	if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0))
		return (NULL);
	line_len = 0;
	if(list == NULL)
	{
		list = malloc(sizeof(t_list));
		if (!list)
			return (NULL);
		list->head = NULL;
		list->tail = NULL;
	}
	if (!create_list(&list, fd, &line_len))
		return (NULL);
	next_line = malloc((line_len + 1) * sizeof(*next_line));
	next_line_head = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!next_line || !next_line_head)
	{
		free_list(&list);
		return (NULL);
	}
	copy_list_to_line(&list, next_line, next_line_head);
	polish(&list, next_line_head);
	return (next_line);
}


int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY | O_CREAT);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	int i = 1;
	while (line)
	{
		printf("line %d: %s\n", i++, line);
		line = get_next_line(fd);
	}

	free(line);
	return (0);
}
