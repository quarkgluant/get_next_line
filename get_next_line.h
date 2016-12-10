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

typedef struct		s_list
{
	char			c;
	struct s_list	*next;
}					t_list;

typedef struct		s_list_line
{
	int				fd;
	t_list			*elem;
}					t_list_line;

typedef stuct		s_line
{
	int				fd;
	int				pos_cr;
	char			cr_p;
	char			line[BUFF_SIZE];
	int				type;
	struct s_line	*next
}					t_line;
	
int		get_next_line(const int fd, char **line);
