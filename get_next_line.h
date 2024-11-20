/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:47:12 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/20 19:24:13 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
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
char				*ft_strdup_buffer(const char *s);
t_list				*add_to_list(t_list *list, char *buffer);
t_list				*create_list(t_list *list, int fd);
int					found_newline(t_node *node);
void				free_list(t_list *list);
size_t				count_line_len(t_list *list);
t_list				*reinitialize_list(t_list *list, char *next_line_head);
char 				*copy_list_to_line(t_list *list, char *next_line_head, int line_len);

#endif
