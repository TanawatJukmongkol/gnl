/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:58:11 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/01 20:15:33 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buff	*push_buff(t_file *file)
{
	if (!file->buffer)
	{
		file->buffer = malloc(sizeof(t_buffer));
		if (!file->buffer)
			return (NULL);
		file->buffer->nodes = malloc(sizeof(t_buff));
		if (!file->buffer->nodes)
			return (NULL);
		file->buffer->nodes->data = malloc(BUFFER_SIZE);
		if (!file->buffer->nodes->data)
			return (NULL);
		file->buffer->nodes->next = NULL;
		file->buffer->last = file->buffer->nodes;
		file->offset = 0;
		file->len = 0;
		return (file->buffer->nodes);
	}
	file->buffer->last->next = malloc(sizeof(t_buff));
	file->buffer->last->next->data = malloc(BUFFER_SIZE);
	file->buffer->last->next->next = NULL;
	file->buffer->last = file->buffer->last->next;
	file->len++;
	return (file->buffer->last);
}

t_buff	*keep_buff(t_file *file)
{
	t_buff	*tmp;

	tmp = file->buffer->nodes;
	*file->buffer->nodes = *file->buffer->nodes->next;
	tmp->next = NULL;
	file->buff_re->last->next = tmp;
	file->buff_re->last = tmp;
	file->len--;
	return (file->buff_re->last);
}

t_buff	*reuse_buff(t_file *file)
{
	t_buff	*tmp;

	tmp = file->buff_re->nodes;
	*file->buff_re->nodes = *file->buff_re->nodes->next;
	tmp->next = NULL;
	file->buffer->last->next = tmp;
	file->buffer->last = tmp;
	return (file->buffer->last);
}

void	free_buff(t_buff *buff)
{
	if (buff && buff->data)
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
		next = (*buff)->next;
		callback(tmp);
		tmp = next;
	}
	return (tmp);
}
