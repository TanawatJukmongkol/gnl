/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:42:45 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/11 06:37:13 by tjukmong         ###   ########.fr       */
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
	ssize_t	slen;
	ssize_t	indx;

	slen = 0;
	(void)(fd);
	while (1)
	{
		if (file->buffer && file->buffer->last)
		{
			printf("file len: %lu", file->len);
			indx = file->offset;
			// printf("\n====================================\n");
			// ittr_buff(&file->buffer->nodes, print_shit);
			while (indx < file->size || file->eof)
			{
				if (file->buffer->last->data[indx] == '\0'
					|| file->buffer->last->data[indx] == '\n')
				{
					printf(" string len: %lu\n", slen);
					indx = 0;
					file->str = malloc(slen + 2);
					while (indx < slen)
					{
						file->str[indx] = file->buffer->nodes->data[file->offset];
						file->offset++;
						if (file->offset == BUFFER_SIZE)
						{
							file->offset = 0;
							file->read_state = 0;
							keep_buff(file);
						}
						indx++;
					}
					file->offset++;
					file->str[slen] = '\n';
					file->str[slen + 1] = '\0';
					return (0);
				}
				indx++;
				slen++;
			}
			file->read_state = 0;
		}
		if (!file->eof && !file->read_state)
		{
			if (file->buff_re && file->buff_re->nodes && !reuse_buff(file))
				return (1);
			else if (!push_buff(file))
				return (1);
			file->size = read(fd, file->buffer->last->data, BUFFER_SIZE);
			if (file->size < 0)
				return (1);
			else if (file->size == 0)
			{
				file->eof = 1;
				*file->buffer->last->data = EOF;
			}
			file->read_state = 1;
		}
	}


}

char	*get_next_line(int fd)
{
	static t_file	files[FD_MAX];

	if (fd < 0)
		return (NULL);

	if (files[fd].eof)
	{
		// free_all(&files[fd]);
		printf("\n--- END! ---\n");
		return (NULL);
	}

	if (files[fd].str)
		free(files[fd].str);
	files[fd].str = NULL;

	if (next_line(&files[fd], fd))
		return (NULL);
	
	// printf("\nfile offset: %lu\n", files[fd].offset);

	return (files[fd].str);
}
