/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelgerv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:24:31 by axelgerv          #+#    #+#             */
/*   Updated: 2018/12/07 18:32:21 by axelgerv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <fcntl.h>

int check_ifexist(t_data *list, int fd)
{
	while (list)
	{
		if(fd == list->fd)
			return (0);
		list = list->next;
	}
	return (1);
}

int     main(int c, char **v)
{
	char    *line;
	int     fd;
	int     i;
	int     out;

	if (c >= 2)
	{
		i = 0;
		if (!(fd = open(v[1], O_RDONLY)))
			return (0);
		line = NULL;
		out = get_next_line(fd, &line);
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
