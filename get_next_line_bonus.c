/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakan <stakan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:17:14 by stakan            #+#    #+#             */
/*   Updated: 2022/11/19 14:17:14 by stakan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (0);
	rd_bytes = 1;
	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free (buff);
			return (0);
		}
		buff[rd_bytes] = '\0';
		left_str = ft_strjoin(left_str, buff);
	}
	free (buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	left_str[fd] = ft_read_to_left_str(fd, left_str[fd]);
	if (!left_str[fd])
		return (0);
	line = ft_get_line(left_str[fd]);
	left_str[fd] = ft_new_left_str(left_str[fd]);
	return (line);
}

/*
#include<fcntl.h>
#include<stdio.h>
int main()
{
    int fd = open("test.txt", O_RDONLY);
    int fd1 = open("test1.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_RDONLY);
    int fd3 = open("test3.txt", O_RDONLY);
    int i;
	int fd_arry[4];
	fd_arry[0] = fd;
	fd_arry[1] = fd1;
	fd_arry[2] = fd2;
	fd_arry[3] = fd3;
    char    **str;
    str = (char **)malloc(sizeof(char*) * 15);
    while (i < 4)
    {
		str[i] = get_next_line(fd_arry[i]);
        while(str[i])
		{
			//write(1, str[i], ft_strlen(str[i]));
			printf("%s", str[i]);
			str[i] = get_next_line(fd_arry[i]);
		}
		i++;
    }
}*/