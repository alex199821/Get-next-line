/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:11:37 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/21 02:16:08 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

// #define BUFFER_SIZE 1
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
		return (NULL);
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

char	*ft_strbefore(const char *str, char n)
{
	size_t	i;
	size_t	j;
	char	*result;

	j = 0;
	i = 0;
	while (str[i] != '\0' && str[i] != n)
	{
		i++;
	}
	result = (char *)malloc(i + 1);
	if (result == NULL)
	{
		return (NULL);
	}
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[i] = '\0';
	return (result);
}

char	*read_single_buffer(int fd)
{
	ssize_t	bytes_read;
	char	*buffer;

	buffer = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
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

char	*polish_new_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer || buffer[i] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = ft_substr(buffer, 0, i + 1);
	return (line);
}

char	*create_saved_chars(char *line_read)
{
	char	*saved_chars;
	int		saved_len;
	char	*newline_pos;

	if (line_read && (newline_pos = ft_strchr(line_read, '\n')) != NULL)
	{
		newline_pos++;
		saved_len = ft_strlen(newline_pos);
		saved_chars = (char *)ft_calloc(saved_len + 1, sizeof(char));
		if (saved_chars == NULL)
			return (NULL);
		ft_memmove(saved_chars, newline_pos, saved_len);
		return (saved_chars);
	}
	else
	{
		return (NULL);
	}
}


char	*return_single_line(int fd)
{
	char	*single_buffer;
	char	*line_read = ft_strdup("");
	while (1)
	{
		single_buffer = read_single_buffer(fd);
		if (single_buffer == NULL)
		{
			if (ft_strlen(line_read) > 0)
				return (line_read);
			free(line_read);
			return (NULL);
		}
		line_read = ft_strjoin(line_read, single_buffer);
		if (ft_strchr(line_read, '\n') != NULL || ft_strlen(single_buffer) < BUFFER_SIZE)
		{
			free(single_buffer);
			return (line_read);
		}
		free(single_buffer);
	}
}

char	*get_next_line(int fd)
{
	static char	*saved_chars;
	char		*line_read;
	char		*polished_new_line;

	if (saved_chars != NULL)
	{
		if (ft_strchr(saved_chars, '\n') != NULL)
		{
			polished_new_line = polish_new_line(saved_chars);
			saved_chars = create_saved_chars(saved_chars);
			return (polished_new_line);
		}
	}

	line_read = return_single_line(fd);
	if (line_read == NULL)
	{
		if (saved_chars != NULL)
		{
			polished_new_line = polish_new_line(saved_chars);
			saved_chars = NULL;
			return (polished_new_line);
		}
		return (NULL);
	}

	saved_chars = create_saved_chars(line_read);
	polished_new_line = polish_new_line(line_read);
	return (polished_new_line);
}

// char	*return_single_line(int fd)
// {
// 	char	*single_buffer;
// 	char	*line_read;

// 	line_read = ft_strdup("");
// 	while (1)
// 	{
// 		single_buffer = read_single_buffer(fd);
// 		if (single_buffer == NULL)
// 		{
// 			free(line_read);
// 			return (NULL);
// 		}
// 		line_read = ft_strjoin(line_read, single_buffer);
// 		if (ft_strchr(line_read, '\n') != NULL
// 			|| ft_strlen(single_buffer) != BUFFER_SIZE)
// 		{
// 			free(single_buffer);
// 			return (line_read);
// 		}
// 		free(single_buffer);
// 	}
// }

// char	*get_next_line(int fd)
// {
// 	static char	*saved_chars;
// 	char		*line_read;
// 	char		*temp;
// 	char		*polished_new_line;

// 	if (saved_chars != NULL)
// 	{
// 		temp = saved_chars;
// 		if (ft_strchr(temp, '\n') != NULL)
// 		{
// 			line_read = temp;
// 			saved_chars = create_saved_chars(line_read);
// 			polished_new_line = polish_new_line(line_read);
// 			return (polished_new_line);
// 		}
// 	}
// 	line_read = return_single_line(fd);
// 	if (line_read == NULL && saved_chars != NULL)
// 	{
// 		saved_chars = NULL;
// 		return (temp);
// 	}
// 	saved_chars = create_saved_chars(line_read);
// 	polished_new_line = polish_new_line(line_read);
// 	if (saved_chars != NULL)
// 	{
// 		return (ft_strjoin(temp, polished_new_line));
// 	}
// 	return (polished_new_line);
// }

// int	main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("example.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("Read Line: %s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }