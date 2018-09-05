/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:58:07 by kpeng             #+#    #+#             */
/*   Updated: 2018/09/04 19:44:00 by kpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

void	continue_reading(int fd)
{
	char	buff[100];
	int		flag;

	if ((flag = read(fd, buff, 4)) > 0)
	   printf("\nanother fucntion:%s", buff);	
}

int		main(int ac, char **av)
{
	int		fd;
	int		flag;
	int		count;
	char 	buff[4000];

	fd = open("a.txt", O_RDONLY);
	while ((flag = read(fd, buff, 5)) > 0)
	{
		count += flag;
		break;
	}
	printf("count:%d content: %s\n",count, buff);
	continue_reading(fd);
	close(fd);
	return (0);	
}
