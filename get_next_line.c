/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcadiot <pcadiot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 17:22:14 by pcadiot           #+#    #+#             */
/*   Updated: 2016/12/08 17:22:26 by pcadiot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					initilization(t_line **item, int fd, char *line)
{
	t_line			*line_elem;
	char			*tmp;

	(*item)->nb_cr = 0;
	(*item)->flag_to_free = 0;
}

t_line				*recherche_fd(int fd, t_line *item)
{
	while (item->next)
	{
		return (item->fd == fd ? item : add_elem(fd, item));
		item = item->next;
	}
}

char				*traitement(int fd, t_line **item, char *line)
{
	int				i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			(*item)->nb_cr++;
			(*item)->pos_cr = i;
			(*item)->line = line;
		}
		i++;
	}
}

int					get_next_line(const int fd, char **line)
{
	int				bytes_read;
	static t_line	*line_elem;
	char			*tmp;
	int				i;

	line_elem = recherche_fd(fd);
	if (!(tmp = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (GNL_PB);
	i = 0;
	while (i < BUFF_SIZE)
		tmp[i++] = '\0';
	while ((bytes_read = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		*line = traitement(fd, &line_elem, tmp);
	}
}
