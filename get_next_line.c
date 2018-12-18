/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelgerv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:32:48 by axelgerv          #+#    #+#             */
/*   Updated: 2018/12/18 15:02:29 by axelgerv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	del_list(t_data **element, int fd)
{
	t_data *before;
	t_data *to_free;

	to_free = *element;
	before = NULL;
	while (to_free->fd != fd)
	{
		before = to_free;
		to_free = to_free->next;
	}
	if (before)
		before->next = to_free->next;
	else
		*element = to_free->next;
	ft_strdel(&to_free->str);
	free(to_free);
}

static t_data	*new_list(int fd)
{
	t_data *new;

	if (!(new = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	new->fd = fd;
	new->str = NULL;
	new->next = NULL;
	return (new);
}

static t_data	*check_fd(int fd, t_data *element)
{
	t_data *new;

	if (element->next && element->fd != fd)
		return (check_fd(fd, element->next));
	if (element->fd == fd)
		return (element);
	new = new_list(fd);
	element->next = new;
	return (new);
}

static int		storage(t_data **head, char **line, int fd)
{
	char	*rest;
	char	*str;
	t_data	*element;

	element = check_fd(fd, *head);
	str = element->str;
	if (!str || !*str)
	{
		del_list(head, fd);
		return (0);
	}
	if ((rest = ft_strchr(str, '\n')))
		*rest = '\0';
	if (!(*line = ft_strdup(str)))
		return (-1);
	if (rest)
	{
		if (!(element->str = ft_strdup(rest + 1)))
			return (-1);
		ft_strdel(&str);
	}
	else
		ft_strdel(&element->str);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	t_data			*element;
	static t_data	*head;
	char			*buf;
	int				rd;

	if (fd < 0 || !line || !(buf = ft_strnew(BUFF_SIZE)) ||
			(!head && (!(head = new_list(fd)))))
		return (-1);
	element = check_fd(fd, head);
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		element->str = ft_strjoinf(&(element->str), &buf, 1);
		ft_strclr(buf);
		if (ft_strchr(element->str, '\n'))
			break ;
	}
	ft_strdel(&buf);
	return (rd >= 0 ? storage(&head, line, fd) : -1);
}
