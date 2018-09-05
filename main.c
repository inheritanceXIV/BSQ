/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 15:09:38 by kpeng             #+#    #+#             */
/*   Updated: 2018/09/04 00:37:25 by kpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_map_info
{
	int		size;
	int		line_length;
	char	empty;
	char 	obstacle;
	char	full;
}				t_map_info;

typedef struct s_list
{
	char			data;
	struct s_list	*next;
}				t_list;

typedef	struct s_biggest
{
	int		row;
	int		col;
	int		dimension;
}				t_biggest;

typedef struct s_map
{
	int		num;
	char 	sym;
}				t_map;

t_biggest	*g_square;

/**util**/
int		min(int	a, int	b, int c)
{
	if (a <= b && a <= c)
		return a;
	else if (b <= c && b <= a)
		return b;
	else
		return c;
}

/**util**/
t_list	*ft_create_elem(char data)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (elem != NULL)
	{
		elem->data = data;
		elem->next = NULL;
	}
	return (elem);
}
 
/**util**/
void	ft_list_push_back(t_list **first_line, char data)
{
	t_list	*elem;

	if (first_line && *first_line)
	{
		elem = *first_line;
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = ft_create_elem(data);
	}
	else
		*first_line = ft_create_elem(data);
}

/**util**/
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/**util**/
int		ft_atoi(char *str, int	length)
{
	int		i;
	int		num;

	i = 0;
	num = 0;
	while (i < length)
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

/**map util**/
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
	//printf("row:%d col:%d dimension:%d\n",square->row, square->col, square->dimension);
	return (map);
}

/**map util**/

t_list	ft_read_first_line()


int		ft_parse_argv()
{

	int			in;
	int			flag;
	char		buffer[4242];
	t_map_info	*map_info;
	int			i;
	t_list		*first_line;
	char		*info;
	t_map		**converted_map;

	i = 0;
	info = malloc(sizeof(char) * 20);
	in = open("example.txt", O_RDONLY);
	if (-1 == in)
		return (-1);

	while ((flag = read(in, buffer, 1) > 0))
	{
		if (buffer[0] != '\n')
			info[i] = buffer[0];
		else
			break ;
		i++;
	}
	info[i] = '\0';
	map_info = save_info(info);

	i  = 0;
	first_line = 0;
	while ((flag = read(in, buffer, 1) > 0))
	{
		if (first_line == 0)
			first_line = ft_create_elem(buffer[0]);
		else if (buffer[0] != '\n')
			ft_list_push_back(&first_line, buffer[0]);
		else
			break ;
		i++;
	}
	map_info->line_length = i;
	/*
	printf("size: %d\n", map_info->size);
	printf("empty: %c\n", map_info->empty);
	printf("obstacle: %c\n", map_info->obstacle);
	printf("full: %c\n", map_info->full);
	printf("line_length: %d\n", map_info->line_length);*/
	converted_map = convert_map(*map_info, in, *first_line);
	print_t_map(converted_map, *map_info, *g_square);
	close(flag);
	close(in);
	free(map_info);	
	return (0);
}

int		main(void)
{
	ft_parse_argv();

	return (0);
}
