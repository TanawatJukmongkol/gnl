/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:42:45 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/09 08:05:10 by tjukmong         ###   ########.fr       */
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

int	next_line(t_file *file, int fd)
{
	ssize_t	read_size;
	ssize_t	str_len;
	ssize_t	indx;

	str_len = 0;
	while (1)
	{
		if (file->buff_re && file->buff_re->nodes)
			reuse_buff(file);
		else
			push_buff(file);
		read_size = read(fd, file->buffer->last->data, BUFFER_SIZE);
		if (read_size < 0)
			return (1);
		else if (read_size == 0)
			file->eof = 1;
		indx = 0;
		while (indx < read_size
			&& file->buffer->last->data[indx - 1] != '\n')
			indx++;
		str_len += indx;
		if (file->buffer->last->data[indx - 1] == '\n')
		{
			indx = 0;
			if (file->str)
			{
				free(file->str);
				file->str = NULL;
			}
			file->str = malloc(str_len + 1);
			file->str[str_len] = '\0';
			while (indx < str_len)
			{
				if ((file->offset + indx) == BUFFER_SIZE)
				{
					indx = 0;
					keep_buff(file);
				}
				file->str[indx] = file->buffer->nodes->data[
					(file->offset + indx) % BUFFER_SIZE];
				file->offset++;
				indx++;
			}
			return (0);
		}
	}
}

void	print_shit(t_buff *buff)
{
	printf("[%p]->", buff);
}

char	*get_next_line(int fd)
{
	static t_file	files[FD_MAX];

	if (fd < 0)
		return (free_all(&files[fd]));

	if (next_line(&files[fd], fd))
		return (NULL);
	free_all(&files[fd]);
	return (files[fd].str);
}
