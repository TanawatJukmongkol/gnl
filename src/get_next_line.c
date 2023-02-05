/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:42:45 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/06 06:11:50 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	*free_all(t_file *file)
{
	ittr_buff(&file->buffer->nodes, free_buff);
	ittr_buff(&file->buff_re->nodes, free_buff);
	free(file->buffer);
	free(file->buff_re);
	return (NULL);
}

void	dump_buffer(t_file *file, void *dst, size_t nbytes)
{
	size_t	indx;

	if (nbytes > file->size)
		nbytes = file->size;
	while (file->size > 0)
	{
		indx = 0;
		while (indx < nbytes)
		{
			((char *)dst)[indx] = file->buffer->nodes->data[indx];
			file->size--;
		}
		keep_buff(file);
	}
}

void print_shit (t_buff *buff) {
	printf("%p: data->%p, next->%p\n", buff, buff->data, buff->next);
}

char	*get_next_line(int fd)
{
	static t_file	files[FD_MAX];

	if (fd < 0)
		return (free_all(&files[fd]));
	// next_line(&files[fd], fd);

	while (!files[fd].eof)
	{
		if (!push_buff(&files[fd]))
			free_all(&files[fd]);
		(&files[fd])->size += read(fd,
			&files[fd].buffer->last->data, BUFFER_SIZE);
	}

	free_all(&files[fd]);
	return ("");
}
