/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nngwenya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 23:54:17 by nngwenya          #+#    #+#             */
/*   Updated: 2017/06/19 16:18:32 by nngwenya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

int		read_line(const int fd, char **line)
{
	int read_bytes;
	static char buffer[BUFF_SIZE + 1];
	char *str;

	read_bytes = read(fd, buffer, BUFF_SIZE);
	buffer[BUFF_SIZE] = '\0';
	str = ft_strjoin(*line, buffer);
	free(*line);
	*line = str;

	return (read_bytes);
}

int		get_next_line(const int fd, char **line)
{
	char	*str;
	char	*eol;
	int		read_bytes;

	str = (char *)malloc(sizeof(char));
	eol = ft_strchr(str, '\n');
	while (eol == NULL)
	{
		read_bytes = read_line(fd, &str);
		if (read_bytes <= 0)
			return (read_bytes);
		else
			eol = ft_strchr(str, '\n');
	}
	ft_strncpy(*line, str, ft_strlen(str) - 1);
	eol = ft_strdup(eol + 1);
	free(str);
	str = NULL;
	return (1);
}

int		main(void)
{
	int		fd = open("wethinkcode.txt", O_RDONLY);
	char	*str;
	int		status = 1;
	int		i = 0;

	str = (char *)malloc(sizeof(char));
	status = get_next_line(fd, &str);
	printf("%s\n", str);
	return (0);
}
