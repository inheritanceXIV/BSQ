/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:53:24 by kpeng             #+#    #+#             */
/*   Updated: 2018/09/05 21:53:26 by kpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
#define	MAP_UTILS_H

void	print_t_map(int **map, t_map_info info, t_biggest square);
t_map_info	*save_info(char *info_arr);
int 		**find_square(int **int_map, t_map_info info, int fd);
t_map_set	*convert_map(t_map_info info, int fd, t_list first_line);
int		ft_read_first_line(t_map_info *map_info);

#endif