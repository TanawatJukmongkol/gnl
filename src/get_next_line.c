/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:42:45 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/10 12:28:47 by tjukmong         ###   ########.fr       */
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
	ssize_t	slen;
	ssize_t	indx;

	read_size = 0;
	slen = 0;
	(void)(fd);
	while (1)
	{
		if (file->buffer && file->buffer->last)
		{
			indx = file->offset + 1;
			while (indx < read_size && file->buffer->last->data[indx] != '\n')
			{
				indx++;
				slen++;
			}
			if (file->buffer->last->data[indx] == '\n')
			{
				printf("%lu\n", slen);
				file->str = malloc(slen + 1);
				file->str[slen] = '\0';
				indx = 0;
				while (indx < slen)
				{
					if (file->offset > BUFFER_SIZE)
					{
						file->offset = 0;
						keep_buff(file);
					}
					file->str[indx] = file->buffer->nodes->data[file->offset];
					file->offset++;
					indx++;
				}
				return (0);
			}
		}
		if (!file->eof)
		{
			if (file->buff_re && file->buff_re->nodes && !reuse_buff(file))
				return (1);
			else if (!push_buff(file))
				return (1);
			read_size = read(fd, file->buffer->last->data, BUFFER_SIZE);
			if (read_size < 0)
				return (1);
			else if (read_size == 0)
				file->eof = 1;
		}
	}
}

void	print_shit(t_buff *buff)
{
	printf("[%s]->", buff->data);
}

char	*get_next_line(int fd)
{
	static t_file	files[FD_MAX];

	if (fd < 0)
		return (free_all(&files[fd]));
	if (files[fd].no_line_left)
		return (NULL);
	if (files[fd].str)
		free(files[fd].str);
	files[fd].str = NULL;
	if (next_line(&files[fd], fd))
		return (NULL);
	
	// printf("\nfile offset: %lu\n", files[fd].offset);
	// ittr_buff(&files[fd].buff_re->nodes, print_shit);

	return (files[fd].str);
}
