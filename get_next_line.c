/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelgerv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:32:48 by axelgerv          #+#    #+#             */
/*   Updated: 2018/12/10 18:55:21 by axelgerv         ###   ########.fr       */
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
	while (element)
	{
		if (fd == element->fd)
			return (element);
		element = element->next;
	}
	return (ft_add_list(fd));
}

char	*ft_storage(t_data *element, char **line)
{
	int		i;
	char	*rest;

	i = 0;
	rest = ft_strchr(element->str, '\n');
	if (rest)
		*rest = '\0';
	*line = ft_strdup(element->str);
	if (rest)
		element->str = ft_strdup(rest + 1);
	return (*line);
}

int		get_next_line(const int fd, char **line)
{
	static	t_data	*element;
	char			buf[BUFF_SIZE + 1];
	int				rd;
	int				i;

	i = 0;
	element = ft_check_fd(fd, element);
	rd = 1;
	if (!fd || !line)
		return (-1);
	while ((rd > 0) && (!element->str ||
				(element->str && (!ft_strchr(element->str, '\n')))))
	{
		rd = read(fd, &buf, BUFF_SIZE);
		if (element->str == NULL)
			element->str = ft_strdup(buf);
		else
			element->str = ft_strjoin(element->str, buf);
		ft_strclr(buf);
	}
	ft_storage(element, line);
	ft_putstr("Ca c'est element->str : ");
	ft_putstr(element->str);
	return (0);
}
