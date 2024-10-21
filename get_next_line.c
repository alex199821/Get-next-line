/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:11:37 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/22 00:35:01 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

// #define BUFFER_SIZE 10
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr = (unsigned char)c;
		ptr++;
	}
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*array;
	size_t	totalsize;

	totalsize = count * size;
	array = (char *)malloc(totalsize);
	if (array == NULL)
	{
		return (NULL);
	}
	ft_memset(array, '\0', totalsize);
	return (array);
}

char	*ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if (c == '\0')
	{
		return ((char *)&str[i]);
	}
	return (NULL);
}

char	*ft_strjoin(char const *prefix, char const *suffix)
{
	char	*array;
	size_t	prefixlength;
	size_t	suffixlength;
	size_t	i;

	prefixlength = ft_strlen(prefix);
	suffixlength = ft_strlen(suffix);
	i = 0;
	array = (char *)malloc(prefixlength + suffixlength + 1);
	if (array == NULL)
		return (NULL);
	while (i < (prefixlength))
	{
		array[i] = prefix[i];
		i++;
	}
	while (i < (prefixlength + suffixlength))
	{
		array[i] = suffix[i - prefixlength];
		i++;
	}
	array[i] = '\0';
	return (array);
}

char	*strjoin_shortened(char *buffer, char *tmp)
{
	char	*str;

	str = ft_strjoin(buffer, tmp);
	free(buffer);
	return (str);
}

char	*read_buffer(int fd, char *buffer)
{
	int		bytes_read;
	char	read_data[BUFFER_SIZE + 1];

	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, read_data, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), NULL);
		read_data[bytes_read] = '\0';
		buffer = strjoin_shortened(buffer, read_data);
		if (!buffer)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (buffer);
}

char	*get_single_line(char *buffer)
{
	int		count;
	int		i;
	char	*str;

	count = 0;
	if (!buffer[0])
		return (NULL);
	while (buffer[count] && buffer[count] != '\n')
		count++;
	if (buffer[count] == '\n')
		count++;
	str = ft_calloc(count + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < count)
	{
		str[i] = buffer[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*save_extra_chars(char *buffer)
{
	char	*str;
	int		count_str;
	int		i;
	char	*tmp;

	tmp = buffer;
	count_str = 0;
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (!tmp[i])
		return (free(buffer), NULL);
	str = ft_calloc(ft_strlen(tmp) + 1, sizeof(char));
	if (!str)
		return (free(buffer), NULL);
	i++;
	while (tmp[i])
	{
		str[count_str++] = tmp[i];
		i++;
	}
	str[count_str] = '\0';
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*full_text;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!full_text)
		full_text = NULL;
	full_text = read_buffer(fd, full_text);
	if (!full_text)
		return (NULL);
	line = get_single_line(full_text);
	if (!line)
	{
		free(full_text);
		full_text = NULL;
		return (NULL);
	}
	full_text = save_extra_chars(full_text);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	fd = open("example.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL && i < 5000)
// 	{
// 		i++;
// 		// printf("Read Line: %s", line);
// 		// free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
