/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:42:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/11 15:32:26 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# define FD_MAX	1000
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buff
{
	char			*data;
	struct s_buff	*next;
}				t_buff;

typedef struct s_buffer
{
	t_buff		*nodes;
	t_buff		*last;
}				t_buffer;

typedef struct s_file
{
	t_buffer	*buffer;
	t_buffer	*buff_re;
	size_t		offset;
	size_t		len;
	size_t		size;
	char		*str;
	int			eof;
	int			read_state;
}				t_file;

char	*get_next_line(int fd);

// Buffer functions
t_buff	*push_buff(t_file *file);
t_buff	*keep_buff(t_file *file);
t_buff	*reuse_buff(t_file *file);
void	free_buff(t_buff *buff);
t_buff	*ittr_buff(t_buff **buff, void (*callback)(t_buff *buff));

#endif