/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelgerv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:32:48 by axelgerv          #+#    #+#             */
/*   Updated: 2018/12/13 19:50:08 by axelgerv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_data	*ft_new_list(int fd)
{
	t_data *new;

	if (!(new = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	new->fd = fd;
	new->str = NULL;
	new->next = NULL;
	return (new);
}

t_data	*ft_check_fd(int fd, t_data *element)
{
	t_data *new;

	if (element->next && element->fd != fd)
		return (ft_check_fd(fd, element->next));
	if (element->fd == fd)
		return (element);
	new = ft_new_list(fd);
	element->next = new;
	return (new);
}

int		ft_storage(t_data *element, char **line)
{
	char	*rest;

	if (!element->str || !*element->str)
		return (0);
	if ((rest = ft_strchr(element->str, '\n')))
		*rest = '\0';
	if (!(*line = ft_strdup(element->str)))
		return (-1);
	if (!rest)
		ft_strdel(&element->str);
	else
		element->str = ft_strdup(rest + 1);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	t_data			*element;
	static t_data	*head;
	char			*buf;
	int				rd;

	if (fd < 0 || !line || !(buf = ft_strnew(BUFF_SIZE)) ||
								(!head && (!(head = ft_new_list(fd)))))
		return (-1);
	element = ft_check_fd(fd, head);
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		element->str = ft_strjoinf(&(element->str), &buf, 1);
		ft_strclr(buf);
		if (ft_strchr(element->str, '\n'))
			break ;
	}
	ft_strdel(&buf);
	return (rd >= 0 ? ft_storage(element, line) : -1);
}
