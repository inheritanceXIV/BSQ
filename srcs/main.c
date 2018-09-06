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

#include "../includes/ft_headers.h"
#include "../includes/ft_utils.h"
#include "../includes/map_utils.h"

t_map_info	*ft_read_syms(const char *filename)
{
	int			fd;
	t_map_info	*map_info;
	int			i;
	char		*info;
	char		buffer[14242];

	buffer[0] = 0;
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

int			ft_parse_argv(const char *filename)
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

int			main(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		ft_parse_argv(argv[i]);
		i++;
	}lseek
	return (0);
}
