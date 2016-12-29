/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcadiot <pcadiot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 17:32:25 by pcadiot           #+#    #+#             */
/*   Updated: 2016/12/08 17:32:31 by pcadiot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "libft/libft.h"

# define BUFF_SIZE 1024
# define GNL_OK 1
# define GNL_EOF 0
# define GNL_PB -1
# define s_line (content_line->line)
# define s_last_cr (content_line->last_cr)
# define s_tmp (content_line->tmp)

typedef struct		s_content
{
	int				fd;
	int				pos_last_cr;
	char			*last_cr;
	char			*line;
	char			*tmp;
}					t_content;

int					get_next_line(const int fd, char **line);

#endif
