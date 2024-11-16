/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:47:12 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/16 23:01:11 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>  //for open file
# include <stdio.h>  //printf
# include <stdlib.h> // for malloc
# include <unistd.h> // read

typedef struct s_node
{
	char			*content;
	struct s_node	*next;
}					t_node;

typedef struct s_list
{
	t_node			*head;
	t_node			*tail;
}					t_list;

char				*get_next_line(int fd);
char				*ft_strdup_delim(const char *s, char delimiter,
						int include_delimiter, int *line_len);
void				add_to_node(t_list **list, char *buffer, int *line_len);
void				create_list(t_list **list, int fd, int *line_len);
int					found_newline(t_node *node);

#endif
