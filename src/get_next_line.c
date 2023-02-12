/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:42:45 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/12 22:59:52 by tjukmong         ###   ########.fr       */
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

int	next_line(t_file *file, int fd)
{
	ssize_t	read_len;
	size_t	slen;
	size_t	indx;

	slen = 0;
	while (1)
	{
		if (file->read_state)
		{
			if (file->buffer->nodes->data[0] == EOF)
			{
				free_all(file);
				file->read_state = 2;
				return (1);
			}
			indx = file->offset % BUFFER_SIZE;
			while (indx < BUFFER_SIZE)
			{
				if (file->buffer->last->data[indx] == '\n'
					|| file->buffer->last->data[indx] == EOF)
				{
					if (file->buffer->last->data[indx] == EOF)
					{
						file->read_state = 2;
						file->str = malloc(slen + 1);
					}
					else
						file->str = malloc(slen + 2);
					file->str[slen] = '\0';
					indx = 0;
					while (indx < slen)
					{
						file->str[indx] = file->buffer->nodes->data[
							file->offset % BUFFER_SIZE];
						indx++;
						file->offset++;
						if (file->offset % BUFFER_SIZE == 0)
							keep_buff(file);
					}
					if (file->read_state != 2)
					{
						file->str[slen] = '\n';
						file->str[slen + 1] = '\0';
					}
					file->offset++;
					return (0);
				}
				slen++;
				indx++;
			}
			file->read_state = 0;
		}
		if (!file->eof && !file->read_state)
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
			if (file->eof || read_len < BUFFER_SIZE)
				file->buffer->last->data[read_len] = EOF;
			file->read_state = 1;
		}
	}
}

char	*get_next_line(int fd)
{
	static t_file	files[FD_MAX];
	
	if (fd < 0 || files[fd].read_state == 2)
		return (NULL);
	// if (files[fd].str != NULL)
	// 	free(files[fd].str);
	// files[fd].str = NULL;
	if (next_line(&files[fd], fd))
		return (NULL);
	if (files[fd].read_state == 2)
		free_all(&files[fd]);
	return (files[fd].str);
}
