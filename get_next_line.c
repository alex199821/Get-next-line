/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:11:37 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/19 18:25:33 by macbook          ###   ########.fr       */
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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*ptr1;
	char	*ptr2;

	if (!dst && !src)
	{
		return (NULL);
	}
	ptr1 = (char *)dst;
	ptr2 = (char *)src;
	while (n--)
	{
		*ptr1 = *ptr2;
		ptr1++;
		ptr2++;
	}
	return (dst);
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

char	*ft_strrchr(char *str, char c)
{
	int	i;

	i = ft_strlen(str);
	while (i > -1)
	{
		if (str[i] == c)
		{
			return ((char *)&str[i]);
		}
		i--;
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

// char	*get_next_line(int fd)
// {
// 	char	*read_data;
// 	ssize_t	bytes_read;

// 	read_data = malloc(BUFFER_SIZE + 1);
// 	if (!read_data)
// 		return (NULL);
// 	bytes_read = read(fd, read_data, BUFFER_SIZE);
// 	if (bytes_read <= 0)
// 	{
// 		free(read_data);
// 		return (NULL);
// 	}
// 	return (read_data);
// }

char	*read_all_lines(int fd)
{
	char	*read_data;
	ssize_t	bytes_read;

	read_data = malloc(BUFFER_SIZE + 1);
	if (!read_data)
		return (NULL);
	bytes_read = read(fd, read_data, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(read_data);
		return (NULL);
	}
	read_data[bytes_read] = '\0';
	return (read_data);
}

char	*extract_before_newline(const char *str)
{
	char	*newline_pos;
	size_t	length;
	char	*result;

	newline_pos = strchr(str, '$');
	if (newline_pos != NULL)
	{
		length = newline_pos - str;
		result = (char *)malloc(length + 1);
		if (result != NULL)
		{
			ft_memcpy(result, str, length);
			result[length] = '\0';
		}
		return (result);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;
	char		*all_lines;

	all_lines = malloc(1);
	while (1)
	{
		if (!saved)
		{
			saved = NULL;
		}
		else
		{
			all_lines = ft_strjoin(all_lines, saved);
			// printf("I WANT HOME AND CODE TO WORK\n");
			saved = NULL;
		}
		if (!all_lines)
			return (NULL);
		// all_lines[0] = '\0';
		line = read_all_lines(fd);
		if (!line)
		{
			free(all_lines);
			return (NULL);
		}
		if (ft_strrchr(line, '$') != NULL)
		{
			saved = ft_strdup(ft_strrchr(line, '$'));
			printf("EXTRACT BEFORE NEWLINE: %s\n",
				extract_before_newline(line));
			printf("SAVED: %s\n", saved);
			all_lines = ft_strjoin(all_lines, extract_before_newline(line));
			free(line);
			return (all_lines);
		}
		all_lines = ft_strjoin(all_lines, line);
		free(line);
		if (!all_lines)
			return (NULL);
	}
}

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("example.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		// printf("Print next Line: %s\n", line);
		free(line);
	}
	// while (i < 9)
	// {
	// 	line = get_next_line(fd);
	// 	printf("Print next Line: %s\n", line);
	// 	i++;
	// }
	close(fd);
	return (0);
}

// First our goal is to read amount of buffers in the text and return them into line
// we should keep doing this until we reach 'n' char.
// reading buffer happens accordingly: