/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:09:38 by kpeng             #+#    #+#             */
/*   Updated: 2018/09/05 12:23:57 by kpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_headers.h"
#include "ft_utils.h"

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

char	**return_map(char buf[], int start_poi, int row, int line_length)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = (char **)malloc(sizeof(char *) * row + 1);
	while (i < 10)
	{
		j = 0;
		map[i] = (char *)malloc(sizeof(char) * line_length + 1);
		while (j < line_length)
		{
			map[i][j] = buf[start_poi++];
			j++;
		}
		start_poi++;
		map[i][j] = '\0';
		i++;
	}
	map[i] = (char *)(0);
	return (map);
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

int 		**get_int_map(t_map_info, )

t_map_set	*convert_map(t_map_info info, int fd, t_list first_line)
{
	int			row;
	int			col;
	char		buffer[14242];
	int			flag;
	t_biggest	*square;
	t_map_set	*set;
	int 		**int_map;

	square = malloc(sizeof(t_biggest));
	square->dimension = 0;
	square->row = -1;
	square->col = -1;
	row = 0;
	int_map = malloc(sizeof(int *) * info.size);
	int_map[0] = malloc(sizeof(int) * (info.line_length + 1));
	while (row < info.line_length)
	{
		int_map[0][row] = (first_line.data == info.empty) ? 1 : 0;
		row++;
		if (row != info.line_length)
			first_line = *first_line.next;
		else
			break ;
	}
	int_map[0][row] = -1;

	row = 1;
	while (row < info.size)
	{
		col = 0;
		int_map[row]  = malloc(sizeof(int) * (info.line_length + 1));
		flag = read(fd, buffer, info.line_length + 1);
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
	set = (t_map_set *)malloc(sizeof(t_map_set));
	set->map = int_map;
	set->square = square;
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

t_map_info	*ft_read_syms(const char *filename)
{
	int			fd;
	t_map_info	*map_info;
	int			i;
	char		*info;
	char		buffer[4242];

	i = 0;
	info = malloc(sizeof(char) * 20);
	fd = open(filename, O_RDONLY);
	if (-1 == fd)
		return (t_map_info *)(0);
	while ((read(fd, buffer, 1) > 0))
	{
		if (buffer[0] != '\n')
			info[i] = buffer[0];
		else
			break ;
		i++;
	}
	info[i] = '\0';
	map_info = save_info(info);
	map_info->fd = fd;
	map_info->line_length = ft_read_first_line(map_info);
	return (map_info);
}

int		ft_parse_argv(const char *filename)
{
	t_map_info	*map_info;
	t_map_set	*map_set;

	map_info = ft_read_syms(filename);
	map_set = convert_map(*map_info, map_info->fd, map_info->first_line);
	print_t_map(map_set->map, *map_info, *g_square);
	free(map_info);	
	free(map_set->map);
	return (0);
}

int		main(int argc, char **argv)
{
	int		i;
	char    *str;

	i = 1;
	while (i < argc)
	{
		ft_parse_argv(argv[i]);
		i++;
	}
	return (0);
}
