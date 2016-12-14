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

int					init_one_link(t_line **item, int fd, char *line)
{
	t_line			*line_elem;
	char			*tmp;

	(*item)->nb_cr = 0;
	(*item)->flag_to_free = 0;
	(*item)->fd = fd;
	(*item)->line = line;
}

t_line				*recherche_fd(int fd, t_line **item)
{
	t_line			*line_elem;

	while ((*item)->next)
	{
		if ((*item)->fd == fd)
			return (*item);
		*item = (*item)->next;
	}
	ft_lstnew(fd, *item)
	return ()
}

char				*traitement(int fd, t_line **item, char *line, char **ret)
{
	int				i;
	int				start;

	if (*line_elem == NULL)
		*line_elem = ft_lstnew(*item, sizeof(item));
	*item = recherche_fd(fd);
/*
	(*item)->line = ft_lstnew(*item, sizeof(item));
	i = 0;
	while (line[i])
	{
		start = i;
		if (line[i] == '\n')
		{
			(*item)->nb_cr++;
			(*item)->pos_last_cr = i;
		}
		i++;
	}
*/
}

int					get_next_line(const int fd, char **line)
{
	int				bytes_read;
	static t_line	*line_elem;
	char			*tmp;
	int				i;

	if (fd < 0 || !(*line = (char *)malloc(sizeof(char) * BUFF_SIZE)))
		return (GNL_PB);
	if (!(tmp = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (GNL_PB);
	i = 0;
	while (i < BUFF_SIZE)
		tmp[i++] = '\0';
	while ((bytes_read = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		*line = traitement(fd, &line_elem, tmp, line);
	}
}
