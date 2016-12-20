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

	if (!(line_elem = (t_content *)malloc(sizeof(t_content))))
		return (NULL);
	line_elem->pos_last_cr = 0;
	line_elem->fd = fd;
	return (line_elem);
}

t_list				*recherche_fd(int fd, t_list **item)
{
	t_list			*line_elem;
	t_content		*content_line

	while ((*item)->next)
	{
		content_line = (t_content *)(*item)->content;
		if (content_line->fd == fd)
			return (*item);
		*item = (*item)->next;
	}
	if (!(content_line = init_one_link(fd)))
		return (NULL);
	line_elem = ft_lstnew(content_line, sizeof(content_line));
	ft_lstadd(item, line_elem);
	line_elem = *item;
	return (line_elem);
}

char				*traitement(t_list *item, char **line)
{
	size_t			start;
	t_content		*content_line

	start = 0;
	content_line = (t_content *)item->content;
	if ((start = ft_strchr(content_line->line, '\n')))
	{
		if (!(*line = ft_strsub(content_line->line, content_line->pos_last_cr, 
					start - content_line->pos_last_cr)))
			return (-1);
		content_line->pos_last_cr = start;
		if (start < ft_strlen(content_line->line))
			content_line->line += ++start;
		else
			ft_strclr(content_line->line);
	}
	return (start);
}

int					get_next_line(const int fd, char **line)
{
	int				bytes_read;
	static t_list	*line_elem;
	char			*buf;
	t_list			*cur;
	t_content		*content_line

	if (fd < 0 || !(*line = ft_strnew(1)) || !(buf = ft_strnew(BUFF_SIZE + 1)))
		return (GNL_PB);
	cur = recherche_fd(fd, &line_elem);
	while ((bytes_read = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[bytes_read] = '\0';
		content_line = (t_content *)cur->content;
		if (!(content_line->line = ft_strjoin(content_line->line, buf)))
			return (GNL_PB);
		if ((content_line->pos_last_cr = ft_strchr(buf, '\n')))
			break ;
	}
	if (ret < BUFF_SIZE && !ft_strlen(content_line->line))
		return (GNL_EOF);
	if (traitement(cur, line) == -1)
		return (GNL_PB);
	free(buf);
	return (GNL_OK);
}
