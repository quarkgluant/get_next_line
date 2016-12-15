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

int					init_one_link(t_list **item, int fd, char *line)
{
	t_content		line_elem;
	char			*tmp;

	line_elem.nb_cr = 0;
	line_elem.flag_to_free = 0;
	line_elem.fd = fd;
	line_elem.line = line;
}

t_list				*recherche_fd(int fd, t_list **item)
{
	t_list			*line_elem;

	while ((*item)->next)
	{
		if ((*item)->fd == fd)
			return (*item);
		*item = (*item)->next;
	}
	line_elem = ft_lstnew("\0", fd);
	ft_lstadd(item, line_elem);
	line_elem = *item;
	return (line_elem);
}

char				*traitement(int fd, t_list **item, char *line, char **ret)
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
	if (!(tmp = ft_strnew(BUFF_SIZE + 1)))
		return (GNL_PB);
	i = 0;
	while ((bytes_read = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		*line = traitement(fd, &line_elem, tmp, line);
	}
}
