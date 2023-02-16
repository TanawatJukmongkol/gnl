/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:42:45 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/16 19:07:18 by tjukmong         ###   ########.fr       */
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

void	print_shit(t_buff *buff)
{
	printf("[%s]->", buff->data);
}

int	read_next(t_file *file, int fd)
{
	ssize_t	read_len;

	if (!file->eof)
	{
		if (file->buff_re && file->buff_re->nodes && !reuse_buff(file))
			return (1);
		else if (!push_buff(file))
			return (1);
		read_len = read(fd, file->buffer->last->data, BUFFER_SIZE);
		file->size += read_len;
		if (read_len < 0)
			return (1);
		else if (read_len == 0)
			file->eof = 1;
		if (read_len < BUFFER_SIZE)
			file->buffer->last->data[read_len] = EOF;
	}
	return (0);
}

/**
ittr_buff(&file->buffer->nodes, print_shit);
		printf("\n");
		keep_buff(file);
**/

int	next_line(t_file *file, int fd)
{
	size_t	slen;
	size_t	indx;

	slen = 0;
	if (file->read_state < 2)
		file->read_state = 0;
	while (file->read_state == 0)
	{
		indx = file->offset % BUFFER_SIZE;
		if (read_next(file, fd))
			return (1);
		while (indx < BUFFER_SIZE)
		{
			if (file->buffer->last->data[indx] == '\n')
				file->read_state = 1;
			if (file->buffer->last->data[indx] == EOF)
			{
				file->read_state = 1;
				slen--;
			}
			indx++;
			slen++;
		}
	}
	indx = 0;
	printf("%-3lu|", slen);
	while (indx < slen)
	{
		printf("%c", file->buffer->nodes->data[file->offset % BUFFER_SIZE]);
		indx++;
		file->offset++;
		if (file->offset % BUFFER_SIZE == 0)
			keep_buff(file);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_file	files[FD_MAX];

	if (fd < 0 || files[fd].read_state == 2)
		return (NULL);
	if (next_line(&files[fd], fd))
		return (NULL);
	if (files[fd].read_state == 2)
		free_all(&files[fd]);
	return (files[fd].str);
}
