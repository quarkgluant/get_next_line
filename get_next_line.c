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
	t_content		*content_line;

	if (!(content_line = (t_content *)malloc(sizeof(t_content))))
		return (NULL);
	content_line->pos_last_cr = 0;
	content_line->fd = fd;
	s_last_cr = NULL;
	s_tmp = NULL;
	if (!(s_line = ft_strnew(0)))
	{
		ft_memdel((void **)&content_line);
		return (NULL);
	}
	return (content_line);
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
	if (!(content_line = init_one_link(fd)))
		return (NULL);
	if (!(line_elem = ft_lstnew(content_line, sizeof(t_content))))
	{
		ft_strdel(&s_line);
		ft_memdel((void **)&content_line);
		return (NULL);
	}
	ft_lstadd(item, line_elem);
	ft_memdel((void **)&content_line);
	line_elem = *item;
	return (line_elem);
}

int					traitement(t_list **item, char **line)
{
	t_content		*content_line;
	int				pos;
	char			*tmp;

	content_line = (t_content *)((*item)->content);
	s_last_cr = ft_strchr(s_line, '\n');
	pos = s_last_cr ? s_last_cr - s_line : ft_strlen(s_line);
	if (!(tmp = ft_strsub(s_line, 0, pos)))
	{
		ft_strdel(&s_line);
		ft_memdel((void **)&content_line);
		return (-1);
	}
	*line = tmp;
	content_line->pos_last_cr = pos;
	if (pos < (int)ft_strlen(s_line))
		s_line += ++pos;
	else
		ft_strclr(s_line);
	return (pos);
}

int					get_next_line(const int fd, char **line)
{
	int				bytes_read;
	static t_list	*line_elem;
	char			buf[BUFF_SIZE + 1];
	t_list			*cur;
	t_content		*content_line;

	if (fd < 0 || !line || !(*line = "") || read(fd, buf, 0) < 0)
		return (GNL_PB);
	cur = recherche_fd(fd, &line_elem);
	content_line = (t_content *)(cur->content);
	while ((bytes_read = read(fd, buf, BUFF_SIZE)))
	{
		buf[bytes_read] = '\0';
		if (!(s_tmp = ft_strjoin(s_line, buf)))
			return (GNL_PB);
		free(s_line);
		s_line = s_tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (bytes_read < BUFF_SIZE && !ft_strlen(s_line))
		return (GNL_EOF);
	return (traitement(&cur, line) < 0 ? GNL_PB : GNL_OK);
}
