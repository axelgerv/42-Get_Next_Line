/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelgerv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:33:37 by axelgerv          #+#    #+#             */
/*   Updated: 2018/12/10 18:58:22 by axelgerv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 5

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef	struct		s_data
{
	char			*str;
	char			*tmp;
	int				fd;
	struct s_data	*next;
}					t_data;

int					check_ifexist(t_data *list, int fd);
t_data				*ft_add_list(int fd);
int					get_next_line(const int fd, char **line);

#endif
