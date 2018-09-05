/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:09:38 by kpeng             #+#    #+#             */
/*   Updated: 2018/09/05 11:57:32 by kpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_headers.h"
#include "ft_utils.h"

void	print_map(int **map, t_map_info info)
{
	int 	i;
	int		j;

	i = 0;
	j = 0;
	while (i < info.size)
	{
		j = 0;
		while (j < info.line_length)
		{
			ft_putchar(map[i][j] + '0');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

void	print_t_map(t_map **map, t_map_info info, t_biggest square)
{
	int 	i;
	int		j;

	i = 0;
	j = 0;
	while (i < info.size)
	{
		j = 0;
		while (j < info.line_length)
		{
			if ((i > square.row - square.dimension && i <= square.row)
				&& (j > square.col - square.dimension && j <= square.col ))
			ft_putchar(info.full);
			else
				ft_putchar(map[i][j].sym);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}


/**map util**/
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

/**map util**/
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

t_map	**convert_map(t_map_info info, int fd, t_list first_line)
{
	int			row;
	int			col;
	char		buffer[4242];
	int			flag;
	int			dimension;
	t_biggest	*square;
	t_map 		**map;

	square = malloc(sizeof(t_biggest));
	square->dimension = 0;
	square->row = 0;
	square->col = 0;
	row = 0;
	map = malloc(sizeof(t_map) * info.size);
	map[0] = malloc(sizeof(t_map) * (info.line_length + 1));
	while (row < info.line_length)
	{
		map[0][row].num = (first_line.data == info.empty) ? 1 : 0;
		map[0][row].sym = first_line.data;
		row++;
		if (row != info.line_length)
			first_line = *first_line.next;
		else
			break ;
	}
	map[0][row].num = -1;
	row = 1;
	while (row < info.size)
	{
		col = 0;
		map[row] = malloc(sizeof(t_map) * (info.line_length + 1));
		flag = read(fd, buffer, info.line_length + 1);
		while (col < info.line_length)
		{
			if (col != 0 && buffer[col] == info.empty)
			{
				dimension = (min(map[row][col - 1].num, map[row - 1][col].num, map[row - 1][col - 1].num)) + 1;
				map[row][col].num = dimension;
				map[row][col].sym = buffer[col];
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
			{
				map[row][col].num =  (buffer[col] == info.empty) ? 1 : 0;
				map[row][col].sym = buffer[col];
			}
			col++;
		}
		map[row][col].num = -1;
		row++;
	}
	g_square = square;
	return (map);
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
	map_info = save_info(info);
	map_info->fd = fd;
	map_info->line_length =  ft_read_first_line(map_info);
	info[i] = '\0';
	return (map_info);
}

int		ft_parse_argv(const char *filename)
{
	t_map		**converted_map;
	t_map_info	*map_info;

	map_info = ft_read_syms(filename);
	converted_map = convert_map(*map_info, map_info->fd, map_info->first_line);
	print_t_map(converted_map, *map_info, *g_square);


	close(map_info->fd);
	free(map_info);	
	free(converted_map);
	return (0);
}

int		main(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		ft_parse_argv(argv[i]);
		i++;
	}
	return (0);
}
