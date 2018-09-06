/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:48:20 by kpeng             #+#    #+#             */
/*   Updated: 2018/09/05 21:48:26 by kpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_headers.h"
#include "../includes/ft_utils.h"

void	print_t_map(int **map, t_map_info info, t_biggest square)
{
	int 	i;
	int		j;
	char 	*str;
	int		index;
	int		str_length;

	index = 0;
	str_length = info.size * info.line_length + info.size;
	str = (char *)malloc(sizeof(char) * str_length);
	close(info.fd);
	i = -1;
	while (++i < info.size)
	{
		j = -1;
		while (++j < info.line_length)
		{
			if (i > square.row - square.dimension && i <= square.row)
				if (j > square.col - square.dimension && j <= square.col)
					str[index] = info.full;
				else
					str[index] = (map[i][j] > 0) ? info.empty : info.obstacle;
			else
				str[index] = (map[i][j] > 0) ? info.empty : info.obstacle;
			index++;
		}
		str[index++] = '\n';
	}
	write(1, str, str_length);
	free(str);
}

t_map_info	*save_info(char *info_arr)
{
	int			len;
	t_map_info	*map_info;

	map_info = malloc(sizeof(t_map_info));
	len = 0;
 	while (info_arr[len] != 0)
 		len++;
	map_info->full = info_arr[len - 1];
	map_info->obstacle = info_arr[len - 2];
	map_info->empty = info_arr[len - 3];
	map_info->size = ft_atoi(info_arr, len - 3);
	return (map_info);
}

int 		**find_square(int **int_map, t_map_info info, int fd)
{
	int			row;
	int			col;
	t_biggest	*square;
	char		buffer[14242];
	int 		dimension;

	square = malloc(sizeof(t_biggest));
	square->row = -1;
	row = 1;
	while (row < info.size)
	{
		col = 0;
		int_map[row]  = malloc(sizeof(int) * (info.line_length + 1));
		read(fd, buffer, info.line_length + 1);
		while (col < info.line_length)
		{
			if (col != 0 && buffer[col] == info.empty)
			{
				dimension = (min(int_map[row][col - 1], int_map[row - 1][col], int_map[row - 1][col - 1])) + 1;
				int_map[row][col]= dimension;
				if (dimension >= square->dimension)
				{
					if (dimension > square->dimension \
						|| (row <= square->row && col <= square-> col))
					{
						square->row = row;
						square->col = col;
					}
					square->dimension = dimension;
				}
			}
			else
				int_map[row][col] =  (buffer[col] == info.empty) ? 1 : 0;
			col++;
		}
		int_map[row][col] = -1;
		row++;
	}
	g_square = square;
	return (int_map);
}

t_map_set	*convert_map(t_map_info info, int fd, t_list first_line)
{
	char		buffer[14242];
	t_map_set	*set;
	int 		**int_map;
	int			col;

	buffer[0] = (col = 0);
	int_map = malloc(sizeof(int *) * info.size);
	int_map[0] = malloc(sizeof(int) * (info.line_length + 1));
	while (col < info.line_length)
	{
		int_map[0][col] = (first_line.data == info.empty) ? 1 : 0;
		col++;
		if (col!= info.line_length)
			first_line = *first_line.next;
		else
			break ;
	}
	int_map[0][col] = -1;

	int_map = find_square(int_map, info, fd);
	set = (t_map_set *)malloc(sizeof(t_map_set));
	set->map = int_map;
	set->square = g_square;
	return (set);
}


int		ft_read_first_line(t_map_info *map_info)
{
	int			len;
	char		buffer[4242];
	t_list		*first_line;

	len  = 0;
	first_line = 0;
	while ((read(map_info->fd, buffer, 1) > 0))
	{
		if (first_line == 0)
			first_line = ft_create_elem(buffer[0]);
		else if (buffer[0] != '\n')
			ft_list_push_back(&first_line, buffer[0]);
		else
			break ;
		len++;
	}
	map_info->first_line = *first_line;
	return (len);
}
