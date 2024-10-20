/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:11:37 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/20 03:22:58 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

// #define BUFFER_SIZE 42
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

char	*read_all_lines(int fd)
{
	char	*read_data;
	char	*temp;
	char	*line;
	ssize_t	bytes_read;

	read_data = malloc(BUFFER_SIZE + 1);
	line = malloc(1);
	if (!read_data || !line)
		return (NULL);
	line[0] = '\0';
	while ((bytes_read = read(fd, read_data, BUFFER_SIZE)) > 0)
	{
		read_data[bytes_read] = '\0';
		temp = ft_strjoin(line, read_data);
		if (!temp)
		{
			free(temp);
			return (NULL);
		}
		free(line);
		line = temp;
	}
	free(read_data);
	return (line);
}

// char	*read_line(int fd)
// {
// 	char	*read_data;
// 	char	*temp;
// 	char	*line;
// 	ssize_t	bytes_read;
// 	char	*newline_pos;

// 	read_data = malloc(BUFFER_SIZE + 1);
// 	line = malloc(1);
// 	if (!read_data || !line)
// 		return (NULL);
// 	line[0] = '\0';
// 	while ((bytes_read = read(fd, read_data, BUFFER_SIZE)) > 0)
// 	{
// 		read_data[bytes_read] = '\0';
// 		// Check if '\n' is found
// 		newline_pos = ft_strchr(read_data, '\n');
// 		if (newline_pos)
// 		{
// 			*newline_pos = '\0'; // Split at '\n'
// 			temp = ft_strjoin(line, read_data);
// 			if (!temp)
// 			{
// 				free(temp);
// 				return (NULL);
// 			}
// 			free(line);
// 			line = temp;
// 			break ;
// 		}
// 		// No newline found, join full buffer
// 		temp = ft_strjoin(line, read_data);
// 		if (!temp)
// 		{
// 			free(temp);
// 			return (NULL);
// 		}
// 		free(line);
// 		line = temp;
// 	}
// 	free(read_data);
// 	if (bytes_read <= 0 && line[0] == '\0')
// 	{
// 		free(line);
// 		return (NULL); // Handle EOF or error
// 	}
// 	return (line);
// }

char	*get_single_line(char *buffer, int *i)
{
	size_t	start;
	char	*line;

	if (!buffer || buffer[*i] == '\0')
		return (NULL);
	start = *i;
	while (buffer[*i] != '\n' && buffer[*i] != '\0')
		(*i)++;
	if (buffer[*i] == '\n')
	{
		line = ft_substr(buffer, start, *i - start + 1);
		(*i)++;
	}
	else
	{
		line = ft_substr(buffer, start, *i - start + 1);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*full_text;
	static int	i;
	char		*line;

	if (!full_text)
		full_text = NULL;
	if (i == 0)
		i = 0;
	if (!full_text)
	{
		full_text = read_all_lines(fd);
		if (!full_text)
		{
			// free(full_text);
			return (NULL);
		}
	}
	if (!full_text)
	{
		free(full_text);
		return (NULL);
	}
	line = get_single_line(full_text, &i);
	if (line == NULL)
	{
		free(full_text);
		full_text = NULL;
		i = 0;
	}
	// full_text = NULL;
	// free(full_test);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	// Open the file
// 	fd = open("example.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("Print next Line: %s", line);
// 		free(line); // Free each line after use
// 	}
// 	close(fd); // Don't forget to close the file descriptor
// 	return (0);
// }

// int	main(void)
// {
// 	int fd;
// 	char c;
// 	char *line;

// 	// Open the file
// 	fd = open("example.txt", O_RDWR);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		exit(EXIT_FAILURE);
// 	}

// 	// Test 1: Read the first line using get_next_line
// 	line = get_next_line(fd);
// 	if (line)
// 	{
// 		printf("Line read: %s", line); // It should print the first line
// 		free(line);
// 	}
// 	else
// 	{
// 		printf("Error: Failed to read the first line.\n");
// 		close(fd);
// 		return (1);
// 	}

// 	// Test 2: Read one character after the newline
// 	if (read(fd, &c, 1) == 1)
// 	{
// 		// Check if the character is '1'
// 		if (c == '1')
// 		{
// 			printf("Test passed: next character is '1'.\n");
// 		}
// 		else
// 		{
// 			printf("Test failed: expected '1', but got '%c'.\n", c);
// 		}
// 	}
// 	else
// 	{
// 		printf("Error: Failed to read the character after the newline.\n");
// 	}

// 	// Close the file
// 	close(fd);
// 	return (0);
// }