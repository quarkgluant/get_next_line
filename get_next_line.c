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
	t_content		*line_elem;

	if (!(line_elem = (t_content *)malloc(sizeof(t_content))))
		return (NULL);
	line_elem->pos_last_cr = 0;
	line_elem->fd = fd;
	line_elem->last_cr = NULL;
	line_elem->line = ft_strnew(0);
	return (line_elem);
}

t_list				*recherche_fd(int fd, t_list **item)
{
	t_list			*line_elem;
	t_content		*content_line;

	line_elem = *item;
	while (line_elem)
	{
		content_line = (t_content *)(line_elem->content);
		if (content_line->fd == fd)
			return (line_elem);
		line_elem = line_elem->next;
	}
	content_line = init_one_link(fd);
	if (content_line == NULL)
		return (NULL);
	line_elem = ft_lstnew(content_line, sizeof(t_content));
	ft_lstadd(item, line_elem);
	line_elem = *item;
	return (line_elem);
}

int					traitement(t_list **item, char **line)
{
	t_content		*content_line;
	int				pos;

	content_line = (t_content *)((*item)->content);
	content_line->last_cr = ft_strchr(content_line->line, '\n');
	pos = content_line->last_cr ? content_line->last_cr - content_line->line :
		ft_strlen(content_line->line);
	if (!(*line = ft_strsub(content_line->line, 0, pos)))
		return (-1);
	content_line->pos_last_cr = pos;
	if (pos < (int)ft_strlen(content_line->line))
		content_line->line += ++pos;
	else
		ft_strclr(content_line->line);
	return (pos);
}

int					get_next_line(const int fd, char **line)
{
	int				bytes_read;
	static t_list	*line_elem;
	char			buf[BUFF_SIZE + 1];
	t_list			*cur;
	t_content		*content_line;

	if (fd < 0 || !line)
		return (GNL_PB);
	if (!(*line = ft_strnew(0)) || read(fd, buf, 0) < 0)
		return (GNL_PB);
	cur = recherche_fd(fd, &line_elem);
	content_line = (t_content *)(cur->content);
	while ((bytes_read = read(fd, buf, BUFF_SIZE)))
	{
		buf[bytes_read] = '\0';
		if (!(content_line->line = ft_strjoin(content_line->line, buf)))
			return (GNL_PB);
		if ((content_line->last_cr = ft_strchr(buf, '\n')))
			break ;
	}
	if (bytes_read < BUFF_SIZE && !ft_strlen(content_line->line))
		return (GNL_EOF);
	return (traitement(&cur, line) < 0 ? GNL_PB : GNL_OK);
}

int					traitement(t_list **item, char **line)
{
	t_content		*content_line;
	int				pos;

	content_line = (t_content *)((*item)->content);
	content_line->last_cr = ft_strchr(content_line->line, '\n');
	pos = content_line->last_cr ? content_line->last_cr - content_line->line :
		ft_strlen(content_line->line);
	if (!(*line = ft_strsub(content_line->line, 0, pos)))
		return (-1);
	content_line->pos_last_cr = pos;
	if (pos < (int)ft_strlen(content_line->line))
		content_line->line += ++pos;
	else
		ft_strclr(content_line->line);
	return (pos);
}

int					get_next_line(const int fd, char **line)
{
	int				bytes_read;
	static t_list	*line_elem;
	char			buf[BUFF_SIZE + 1];
	t_list			*cur;
	t_content		*content_line;

	if (fd < 0 || !line)
		return (GNL_PB);
	if (!(*line = ft_strnew(1)) || read(fd, buf, 0) < 0)
		return (GNL_PB);
	cur = recherche_fd(fd, &line_elem);
	content_line = (t_content *)(cur->content);
	while ((bytes_read = read(fd, buf, BUFF_SIZE)))
	{
		buf[bytes_read] = '\0';
		if (!(content_line->line = ft_strjoin(content_line->line, buf)))
			return (GNL_PB);
		if ((content_line->last_cr = ft_strchr(buf, '\n')))
			break ;
	}
	if (bytes_read < BUFF_SIZE && !ft_strlen(content_line->line))
		return (GNL_EOF);
	if (traitement(&cur, line) < 0)
		return (GNL_PB);
	return (GNL_OK);
}
