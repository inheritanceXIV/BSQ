/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_headers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:45:46 by kpeng             #+#    #+#             */
/*   Updated: 2018/09/05 11:56:27 by kpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADER_H
#define FT_HEADER_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct		s_list
{
	char			data;
	struct s_list	*next;
}					t_list;

typedef struct		s_map_info
{
	int			size;
	int			line_length;
	char		empty;
	char		obstacle;
	char		full;
	int			fd;
	t_list		first_line;
}					t_map_info;


typedef	struct		s_biggest
{
	int			row;
	int			col;
	int			dimension;
}					t_biggest;

typedef struct		s_map
{
	int		num;
	char	sym;
}					t_map;

typedef struct		s_map_set
{
	struct s_map	 	*map;
	struct s_biggest	*square;
}					t_map_set;

t_biggest			*g_square;

#endif
