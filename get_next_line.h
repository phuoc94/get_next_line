/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:47:12 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/22 09:55:01 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 12
# endif

# include <fcntl.h>  //for open file
# include <stdio.h>  //printf
# include <stdlib.h> // for malloc
# include <unistd.h> // read

typedef struct s_mynode
{
	char			*content;
	struct s_mynode	*next;
}					t_mynode;

typedef struct s_list
{
	t_mynode		*head;
	t_mynode		*tail;
}					t_list;

typedef struct s_line_data
{
	char	*current_line;
	char	*next_line;
}				t_line_data;

char				*get_next_line(int fd);
void				add_to_list(t_list *list, char *buffer);
void				create_list(t_list **list, int fd);
int					found_newline(t_mynode *node);
void				free_list(t_list *list);
size_t				count_line_len(t_list *list);
t_list				*reinitialize_list(t_list *list, char *next_line_head);
char				*copy_list_to_line(t_list *list, char *next_line_head,
						int line_len);

#endif
