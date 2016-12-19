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

t_content			*init_one_link(int fd)
{
	t_content		line_elem;

	line_elem.nb_cr = 0;
	line_elem.flag_to_free = 0;
	line_elem.fd = fd;
 	return (&line_elem);
}

t_list				*recherche_fd(int fd, t_list **item)
{
	t_list			*line_elem;
	t_content		*content_line

	while ((*item)->next)
	{
		if ((*item)->fd == fd)
			return (*item);
		*item = (*item)->next;
	}
	content_line = init_one_link(fd, line);
	line_elem = ft_lstnew(content_line, sizeof(content_line));
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
	static t_list	*line_elem;
	char			*buf;
	int				i;
	t_list			*cur;

	if (fd < 0 || !(*line = ft_strnew(1)) || !(buf = ft_strnew(BUFF_SIZE + 1)))
		return (GNL_PB);
	i = 0;
	cur = recherche_fd(fd, &line_elem);
	while ((bytes_read = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[bytes_read] = '\0';
		if (!(cur->content->line = ft_strjoin(cur->content->line, buf)))
			return (GNL_PB);
		if ((cur->content->pos_last_cr = ft_strchr(buf, '\n')))
			break ;
	}
	if (ret < BUFF_SIZE && !ft_strlen(cur->content->line))
		return (GNL_EOF);

}
