/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelgerv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:32:48 by axelgerv          #+#    #+#             */
/*   Updated: 2018/12/12 17:48:10 by axelgerv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_data	*ft_add_list(int fd)
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
	t_data	*new;
	t_data	*head;

	head = element;
	while (element)
	{
		if (element->fd == fd)
			return (element);
		element = element->next;
	}
	new = ft_add_list(fd);
	if (!(element))
		element = new;
	else
	{
		while (element->next)
			element = element->next;
		element->next = new;
	}
	element = head;
	return (new);
}

int		ft_storage(t_data *element, char **line)
{
	int		i;
	char	*rest;

	i = 0;
	rest = ft_strchr(element->str, '\n');
	if (rest)
		*rest = '\0';
	if (!(*line = ft_strdup(element->str)))
		return (-1);
	if (rest)
	{
		if (!(element->str = ft_strdup(rest + 1)))
			return (-1);
	}
	else
		return (0);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static	t_data	*element;
	char			*buf;
	int				rd;

	element = ft_check_fd(fd, element);
	if (fd < 0 || !line || !(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		(element->str = ft_strjoinf(&(element->str),
									&buf, element->str ? 1 : 0));
		if (ft_strchr(element->str, '\n'))
			break ;
	}
	ft_strdel(&buf);
	return (ft_storage(element, line));
}
