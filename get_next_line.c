/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelgerv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:32:48 by axelgerv          #+#    #+#             */
/*   Updated: 2018/12/07 18:32:56 by axelgerv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_data *ft_add_list(t_data *list, int fd)
{
	t_data *new;

	if (!(new = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	new->fd = fd;
	new->str = NULL;
	new->next = NULL;
	return (new);
}

void	copy_until(t_data *list, char *src)
{
	int i;

	i = 0;
	while (src[i] || src[i] != '\n')
	{
		list->str[i] = src[i];
		i++;
	}
}

int get_next_line(const int fd, char **line)
{
	static t_data *element;
	char buf[BUFF_SIZE + 1];
	int rd;
	char *target;
	element = ft_add_list(element, fd);
	while ((rd = read(fd, &buf, BUFF_SIZE)) > 0)
	{
		if (element->str == NULL)
			element->str = ft_memalloc(BUFF_SIZE);
		element->str = ft_strjoin(element->str, buf);
		if ((target = ft_strchr(element->str, '\n')))
		{
		}
	}
	ft_putstr(element->str);
	return (0);
}
