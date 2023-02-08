/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:58:11 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/08 23:26:24 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_buff	*push_buff(t_file *file)
{
	if (!file->buffer)
	{
		file->buffer = malloc(sizeof(t_buffer));
		if (file->buffer != NULL)
			file->buffer->nodes = malloc(sizeof(t_buff));
		if (file->buffer != NULL && file->buffer->nodes != NULL)
			file->buffer->nodes->data = malloc(BUFFER_SIZE);
		if (file->buffer->nodes->data == NULL)
			return (NULL);
		file->buffer->nodes->next = NULL;
		file->buffer->last = file->buffer->nodes;
		file->offset = 0;
		file->len = 1;
		return (file->buffer->nodes);
	}
	file->buffer->last->next = malloc(sizeof(t_buff));
	if (file->buffer->last->next != NULL)
		file->buffer->last->next->data = malloc(BUFFER_SIZE);
	if (file->buffer->last->next->data == NULL)
		return (NULL);
	file->buffer->last = file->buffer->last->next;
	file->buffer->last->next = NULL;
	file->len++;
	return (file->buffer->last);
}

t_buff	*keep_buff(t_file *file)
{
	t_buff	*tmp;

	if (!file->buffer || !file->buffer->nodes)
		return (NULL);
	tmp = file->buffer->nodes;
	file->buffer->nodes = file->buffer->nodes->next;
	if (!file->buff_re)
	{
		file->buff_re = malloc(sizeof(t_buffer));
		if (!file->buff_re)
			return (NULL);
		file->buff_re->nodes = tmp;
		file->buff_re->nodes->next = NULL;
		file->buff_re->last = file->buff_re->nodes;
		file->len--;
		return (file->buff_re->last);
	}
	file->buff_re->last->next = tmp;
	file->buff_re->last->next->next = NULL;
	file->buff_re->last = file->buff_re->last->next;
	file->len--;
	return (file->buff_re->last);
}

t_buff	*reuse_buff(t_file *file)
{
	t_buff	*tmp;

	if (!file->buff_re || !file->buff_re->nodes)
		return (NULL);
	tmp = file->buff_re->nodes;
	file->buff_re->nodes = file->buff_re->nodes->next;
	if (!file->buffer->nodes)
	{
		file->buffer->nodes = tmp;
		file->buffer->nodes->next = NULL;
		file->buffer->last = file->buffer->nodes;
		return (file->buffer->last);
	}
	file->buffer->last->next = tmp;
	file->buffer->last->next->next = NULL;
	file->buffer->last = file->buffer->last->next;
	file->len--;
	return (file->buffer->last);
}

void	free_buff(t_buff *buff)
{
	buff->next = NULL;
	if (buff->data)
		free(buff->data);
	if (buff)
		free(buff);
}

t_buff	*ittr_buff(t_buff **buff, void (*callback)(t_buff *buff))
{
	t_buff	*tmp;
	t_buff	*next;

	if (!buff || !*buff || !callback)
		return (NULL);
	tmp = *buff;
	while (tmp)
	{
		next = tmp->next;
		callback(tmp);
		tmp = next;
	}
	return (tmp);
}
