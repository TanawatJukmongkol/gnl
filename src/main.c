/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:42:14 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/17 13:58:37 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("/home/arch/Projects/Cadet42/get_next_line/test.txt", O_RDONLY);

	while (1)
	{
		str = get_next_line(fd);
		printf("%s", str);
		if (!str)
			break ;
		free(str);
	}
	close(fd);
	return (0);
}
