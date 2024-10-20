/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:11:37 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/20 18:48:05 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

#define BUFFER_SIZE 10
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

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*ptr1;
	const char	*ptr2;

	ptr1 = dst;
	ptr2 = src;
	if (!dst && !src)
		return (NULL);
	if (dst < src)
	{
		while (n--)
		{
			*ptr1++ = *ptr2++;
		}
	}
	else
	{
		while (n--)
		{
			ptr1[n] = ptr2[n];
		}
	}
	return (dst);
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

char	*ft_strdup(const char *src)
{
	size_t	i;
	char	*array;

	i = ft_strlen(src);
	array = (char *)ft_calloc(i + 1, sizeof(char));
	if (array == NULL)
	{
		return (NULL);
	}
	ft_memmove(array, src, i + 1);
	return (array);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*array;

	i = 0;
	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	if (len > ft_strlen(s) - start)
	{
		len = ft_strlen(s) - start;
	}
	array = (char *)malloc(len + 1);
	if (array == NULL)
	{
		return (NULL);
	}
	while (i < len && s[start + i] != '\0')
	{
		array[i] = s[i + start];
		i++;
	}
	array[i] = '\0';
	return (array);
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

// char	*read_single_buffer(int fd, char *line_read, ssize_t total_bytes)
// {
// 	ssize_t	bytes_read;
// 	char	*buffer;

// 	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
// 	if (buffer == NULL)
// 	{
// 		free(buffer);
// 		return (NULL);
// 	}
// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	if (bytes_read <= 0)
// 	{
// 		free(buffer);
// 		return (NULL);
// 	}
// 	total_bytes = total_bytes + bytes_read;
// 	return (buffer);
// }

// char	*get_next_line(int fd)
// {
// 	char	*single_buffer;
// 	ssize_t	total_bytes;
// 	char	*line_read;
// 	char	*temp;

// 	line_read = (char *)ft_calloc(1, sizeof(char));
// 	if (line_read == NULL)
// 	{
// 		free(line_read);
// 		return (NULL);
// 	}
// 	single_buffer = read_single_buffer(fd, single_buffer, total_bytes);
// 	temp = ft_strjoin(line_read, single_buffer);
// 	if (ft_strchr(single_buffer, '$') != NULL)
// 	{
// 		printf("ft_strchr worked\n");
// 		return (NULL);
// 	}
// 	return (single_buffer);
// }

// int	main(void)
// {
// 	int fd;
// 	char *line;
// 	int i;
// 	fd = open("example.txt", O_RDONLY);
// 	i = 0;
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}

// 	while ((line = get_next_line(fd)) != NULL && i < 20)
// 	{
// 		printf("Read Line: %s\n", line);
// 		i++;
// 		free(line);
// 	}

// 	close(fd);
// 	return (0);
// };

char	*read_single_buffer(int fd)
{
	ssize_t	bytes_read;
	char	*buffer;

	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*return_single_line(int fd)
{
	char		*single_buffer;
	char		*line_read;
	static char	*newline_position;
	size_t		len_before_newline;

	line_read = ft_strdup("");
	while (1)
	{
		if (newline_position != NULL)
		{
			line_read = ft_strjoin(line_read, newline_position);
			newline_position = NULL;
		}
		single_buffer = read_single_buffer(fd);
		if (single_buffer == NULL)
		{
			printf("ended whole\n");
			return (NULL);
		}
		line_read = ft_strjoin(line_read, single_buffer);
		if (ft_strchr(line_read, '\n') != NULL)
		{
			newline_position = ft_strchr(line_read, '\n');
			if (newline_position == NULL)
			{
				return (ft_substr(line_read, 0, ft_strlen(line_read)));
			}
			return (ft_substr(line_read, 0, newline_position - line_read));
		}
	}
}

char	*get_next_line(int fd)
{
	char	*single_buffer;
	ssize_t	total_bytes;
	char	*line_read;

	line_read = return_single_line(fd);
	return (line_read);
}

int	main(void)
{
	int fd;
	char *line;
	int i;
	fd = open("example.txt", O_RDONLY);
	i = 0;
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		// printf("Read Line: %s\n", line);
		i++;
		free(line);
	}

	close(fd);
	return (0);
}