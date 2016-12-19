P /* ************************************************************************** */
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
	t_content		*line_elem;

	if ((line_elem = (t_content *)malloc(sizeof(t_content))))
		return (NULL);
	line_elem.pos_last_cr = 0;
	line_elem.fd = fd;
	return (line_elem);
}

t_list				*recherche_fd(int fd, t_list **item)
{
	t_list			*line_elem;
	t_content		*content_line

	while ((*item)->next)
	{
		if ((*item)->content_line->fd == fd)
			return (*item);
		*item = (*item)->next;
	}
	if ((content_line = init_one_link(fd)))
		return (NULL);
	line_elem = ft_lstnew(content_line, sizeof(content_line));
	ft_lstadd(item, line_elem);
	line_elem = *item;
	return (line_elem);
}

char				*traitement(t_list *item, char **line)
{
	size_t			start;

	start = 0;
	if ((start = ft_strchr(item->content->line, '\n')))
	{
		if (!(*line = ft_strsub(item->content->line, item->content->pos_last_cr, 
					start - item->content->pos_last_cr)))
			return (-1);
		line++;
		item->content->pos_last_cr = start;
		if (start < ft_strlen(item->content->line))
			item->content->line += ++start;
		else
			ft_strclr(item->content->line);
	}
	return (start);
}

int					get_next_line(const int fd, char **line)
{
	int				bytes_read;
	static t_list	*line_elem;
	char			*buf;
	t_list			*cur;

	if (fd < 0 || !(*line = ft_strnew(1)) || !(buf = ft_strnew(BUFF_SIZE + 1)))
		return (GNL_PB);
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
	if (traitement(cur, line) == -1)
		return (GNL_PB);
	free(buf);
}
