/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 01:39:26 by macbook           #+#    #+#             */
/*   Updated: 2024/10/22 01:52:55 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
