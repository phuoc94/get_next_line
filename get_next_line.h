/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:47:12 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/16 22:03:51 by phuocngu         ###   ########.fr       */
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

typedef struct s_list
{
	char			*content;
	int				len;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
char				*ft_strdup_delim(const char *s, char delimiter,
						int include_delimiter, int *line_len);
void				add_to_list(t_list **node, char *buffer, int *line_len);
void				create_list(t_list **line_chain, int fd, int *line_len);
int					found_newline(t_list *node);

#endif
