/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:42:14 by tjukmong          #+#    #+#             */
/*   Updated: 2023/02/09 07:44:30 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("/home/arch/Projects/Cadet42/get_next_line/src/main.c", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	close(fd);
	free(str);
	return (0);
}
