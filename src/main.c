/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:42:14 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/16 17:51:58 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	// char	*str;

	fd = open("/home/arch/Projects/Cadet42/get_next_line/test.txt", O_RDONLY);

	int i = 4;
	while (i--)
	{
		// str = get_next_line(fd);
		get_next_line(fd);
		// printf("%s", str);
		// if (!str)
		// 	break ;
		// free(str);
	}

	close(fd);
	return (0);
}
