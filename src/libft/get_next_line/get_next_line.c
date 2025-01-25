/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeters <adeters@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:12:06 by adeters           #+#    #+#             */
/*   Updated: 2025/01/14 18:43:45 by adeters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_check_nl(char *str);
static char	*free_foo(char **buffer, char *line);
static char	*ft_update(char *buffer);
static char	*make_line(char **buffer, char *line, int code);

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;
	ssize_t		bytes_read;

	line = NULL;
	if (fd < 0 || fd >= 1024)
		return (free_foo(&buffer, NULL));
	bytes_read = 1;
	while (!ft_check_nl(buffer) && bytes_read > 0)
	{
		buffer = ft_update(buffer);
		if (!buffer)
			return (NULL);
		bytes_read = read(fd, buffer + ft_strlen(buffer), BUFFER_SIZE);
		if (bytes_read < 0)
			return (free_foo(&buffer, NULL));
	}
	if (ft_check_nl(buffer))
		return (make_line(&buffer, line, 1));
	if (buffer && ft_strlen(buffer))
		line = make_line(&buffer, line, 0);
	free(buffer);
	buffer = NULL;
	return (line);
}

static int	ft_check_nl(char *str)
{
	int	index;

	index = 0;
	if (str == NULL)
		return (0);
	while (str[index])
	{
		if (str[index] == '\n')
			return (1);
		index++;
	}
	return (0);
}

static char	*free_foo(char **buffer, char *line)
{
	free(*buffer);
	free(line);
	*buffer = NULL;
	return (NULL);
}

static char	*ft_update(char *buffer)
{
	char	*tmp_buffer;

	if (buffer == NULL)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, 1);
		if (!buffer)
			return (NULL);
		return (buffer);
	}
	else if (!(ft_check_nl(buffer)))
	{
		tmp_buffer = ft_calloc(BUFFER_SIZE + 1 + ft_strlen(buffer), 1);
		if (!tmp_buffer)
			return (free_foo(&buffer, NULL));
		ft_strlcpy(tmp_buffer, buffer, ft_strlen(buffer) + 1);
		free(buffer);
		return (tmp_buffer);
	}
	tmp_buffer = ft_calloc(ft_strlen(ft_strchr(buffer, '\n') + 1) + 1, 1);
	if (!tmp_buffer)
		return (free_foo(&buffer, NULL));
	ft_strlcpy(tmp_buffer, (ft_strchr(buffer, '\n') + 1),
		ft_strlen(ft_strchr(buffer, '\n') + 1) + 1);
	free(buffer);
	return (tmp_buffer);
}

static char	*make_line(char **buffer, char *line, int code)
{
	if (code == 1)
	{
		line = ft_calloc(1, (ft_strchr(*buffer, '\n') + 1 - *buffer) + 1);
		ft_strlcpy(line, *buffer, (ft_strchr(*buffer, '\n') + 1 - *buffer) + 1);
		*buffer = ft_update(*buffer);
		if (!*buffer || !line)
			return (free_foo(buffer, line));
		return (line);
	}
	line = ft_calloc(1, ft_strlen(*buffer) + 1);
	ft_strlcpy(line, *buffer, ft_strlen(*buffer) + 1);
	*buffer = ft_update(*buffer);
	if (!*buffer || !line)
		return (free_foo(buffer, line));
	return (line);
}

/* #include "get_next_line.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>

int		decode_file(int *lpf, int *f, int *fr, char *str);
int		error_handler(int code);
ssize_t	frame_proc_duration(clock_t start, clock_t end);

int	main(int argc, char **argv)
{
	int 	lines_per_frame; int frames; int frame_rate;
	ssize_t	proc_time; ssize_t delay_time;
	clock_t	start, end;
	char	*str = NULL;

	if (argc != 3)
		return (error_handler(1));
	ssize_t duration = atoi(argv[2]) * 1000000;
	if (duration <= 0)
		return (error_handler(2));
	int fd = open(argv[1], O_RDWR);
	if (fd < 0)
		return (error_handler(3));
	str = get_next_line(fd);
	if (!decode_file(&lines_per_frame, &frames, &frame_rate, str))
		return (error_handler(4));
	delay_time = 1000000 / frame_rate;
	// Play movie for chosen duration
	do {
		int frame_line = 0;
		int index = 0;
		// Print a single frame
		while (index < frames && duration > 0)
		{
			start = clock();
			system("clear");
			frame_line = 0;
			while (frame_line < lines_per_frame)
			{
				if (str)
					free(str);
				str = get_next_line(fd);
				if (str)
					printf("%s", str); fflush(stdout);
				frame_line++;
			}
			duration -= 1000000 / frame_rate;
			index++;
			end = clock();
			proc_time = frame_proc_duration(start, end);
			if (proc_time < delay_time)
				usleep(delay_time - proc_time);
			else
				usleep(delay_time);
		}
		close(fd);
		fd = open(argv[1], O_RDWR);
		str = get_next_line(fd);
	} while (duration > 0);
	system("clear");
	get_next_line(-1);
	free(str);
}

int decode_file(int *lpf, int *f, int *fr, char *str)
{

	*lpf = atoi(str);
	*f = atoi(strchr(str, '-') + 1);
	*fr = atoi(strchr(strchr(str, '-') + 1, '-') + 1);
	if (!*lpf || !*f || !*fr)
		return (0);
	return (1);
}

int	error_handler(int code)
{
	if (code == 1)
	{
		fprintf(stderr, "Usage: ./a.out [file.txt] [duration in s]\n");
		return (1);
	}
	if (code == 2)
	{
		fprintf(stderr, "Not a valid duration");
		return (2);
	}
	if (code == 3)
	{
		fprintf(stderr, "Could not open file.\n");
		return(3);
	}
	if (code == 4)
	{
		fprintf(stderr, "Error reading formating code.\n");
		return (4);
	}
	return (0);
}

ssize_t frame_proc_duration(clock_t start, clock_t end)
{
	return ((ssize_t)((double)(end - start) / CLOCKS_PER_SEC * 1000000));
} */