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

# define BUFF_SIZE 32
# define GNL_OK 1
# define GNL_EOF 0
# define GNL_PB -1

typedef struct		s_line
{
	int				fd;
	int				flag_to_free;
	int				pos_last_cr;
	int				nb_cr;
	char			*line;
	struct s_line	*next
}					t_line;
	
int		get_next_line(const int fd, char **line);
