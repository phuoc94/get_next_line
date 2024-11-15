/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:46:41 by phuocngu          #+#    #+#             */
/*   Updated: 2024/11/16 01:33:31 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


int ft_strlen(const char *str)
{
	int i = 0;
	while (str[i])
		i++;

	return (i);
}


char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	strlen;
	size_t	i;

	strlen = ft_strlen(s);
	ptr = malloc((strlen + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i <= strlen)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}
