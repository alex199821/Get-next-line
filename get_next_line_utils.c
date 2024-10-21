/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:58:57 by macbook           #+#    #+#             */
/*   Updated: 2024/10/21 16:31:13 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// char	*read_single_buffer(int fd, int *num)
// {
// 	ssize_t	bytes_read;
// 	char	*buffer;

// 	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
// 	if (buffer == NULL)
// 		return (NULL);
// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	if (bytes_read <= 0)
// 	{
// 		if (bytes_read == -1)
// 			*num = -1;
// 		free(buffer);
// 		return (NULL);
// 	}
// 	buffer[bytes_read] = '\0';
// 	return (buffer);
// }

// char	*polish_new_line(char *buffer)
// {
// 	int		i;
// 	char	*line;

// 	i = 0;
// 	if (!buffer || buffer[i] == '\0')
// 		return (NULL);
// 	while (buffer[i] != '\n' && buffer[i] != '\0')
// 		i++;
// 	line = ft_substr(buffer, 0, i + 1);
// 	if (line == NULL)
// 		return (NULL);
// 	return (line);
// }

// char	*create_saved_chars(char *line_read)
// {
// 	char	*saved_chars;
// 	char	*newline_pos;

// 	newline_pos = ft_strchr(line_read, '\n');
// 	if (newline_pos)
// 	{
// 		saved_chars = ft_strdup(newline_pos + 1);
// 		if (!saved_chars)
// 			return (NULL);
// 		return (saved_chars);
// 	}
// 	return (NULL);
// }

// char	*return_single_line(int fd, int *num)
// {
// 	char	*single_buffer;
// 	char	*line_read;
// 	char	*temp;

// 	line_read = ft_strdup("");
// 	if (!line_read)
// 		return (NULL);
// 	while (1)
// 	{
// 		single_buffer = read_single_buffer(fd, num);
// 		if (single_buffer == NULL)
// 		{
// 			if (ft_strlen(line_read) > 0)
// 				return (line_read);
// 			free(line_read);
// 			return (NULL);
// 		}
// 		temp = ft_strjoin(line_read, single_buffer);
// 		free(line_read);
// 		free(single_buffer);
// 		if (!temp)
// 			return (NULL);
// 		line_read = temp;
// 		if (ft_strchr(line_read, '\n') != NULL)
// 			return (line_read);
// 	}
// 	return (line_read);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*saved_chars;
// 	char		*line_read;
// 	char		*polished_new_line;
// 	char		*new_saved_chars;
// 	char		*temp_polished_line;
// 	int			num;
// 	char		*result;

// 	num = 0;
// 	temp_polished_line = NULL;
// 	if (saved_chars != NULL && ft_strchr(saved_chars, '\n') != NULL)
// 	{
// 		polished_new_line = polish_new_line(saved_chars);
// 		if (!polished_new_line)
// 			return (NULL);
// 		new_saved_chars = create_saved_chars(saved_chars);
// 		free(saved_chars);
// 		saved_chars = new_saved_chars;
// 		return (polished_new_line);
// 	}
// 	line_read = return_single_line(fd, &num);
// 	if (line_read == NULL)
// 	{
// 		if (saved_chars != NULL)
// 		{
// 			if (num == -1)
// 			{
// 				free(saved_chars);
// 				saved_chars = NULL;
// 				return (NULL);
// 			}
// 			polished_new_line = polish_new_line(saved_chars);
// 			free(saved_chars);
// 			saved_chars = NULL;
// 			return (polished_new_line);
// 		}
// 		return (NULL);
// 	}
// 	if (saved_chars)
// 	{
// 		temp_polished_line = ft_strdup(saved_chars);
// 		free(saved_chars);
// 		if (!temp_polished_line)
// 			return (NULL);
// 	}
// 	saved_chars = create_saved_chars(line_read);
// 	polished_new_line = polish_new_line(line_read);
// 	free(line_read);
// 	if (temp_polished_line != NULL && polished_new_line != NULL)
// 	{
// 		result = ft_strjoin(temp_polished_line, polished_new_line);
// 		free(temp_polished_line);
// 		free(polished_new_line);
// 		return (result);
// 	}
// 	free(temp_polished_line);
// 	return (polished_new_line);
// }
// char	*read_single_buffer(int fd)
// {
// 	ssize_t	bytes_read;
// 	char	*buffer;

// 	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
// 	if (buffer == NULL)
// 		return (NULL);
// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	if (bytes_read <= 0)
// 	{
// 		free(buffer);
// 		return (NULL);
// 	}
// 	buffer[bytes_read] = '\0';
// 	return (buffer);
// }

// char	*polish_new_line(char *buffer)
// {
// 	int		i;
// 	char	*line;

// 	i = 0;
// 	if (!buffer || buffer[i] == '\0')
// 		return (NULL);
// 	while (buffer[i] != '\n' && buffer[i] != '\0')
// 		i++;
// 	line = ft_substr(buffer, 0, i + 1);
// 	if (line == NULL)
// 		return (NULL);
// 	return (line);
// }

// char	*create_saved_chars(char *line_read)
// {
// 	char	*saved_chars;
// 	char	*newline_pos;

// 	newline_pos = ft_strchr(line_read, '\n');
// 	if (newline_pos)
// 	{
// 		saved_chars = ft_strdup(newline_pos + 1);
// 		if (!saved_chars)
// 			return (NULL);
// 		return (saved_chars);
// 	}
// 	return (NULL);
// }

// char	*return_single_line(int fd)
// {
// 	char	*single_buffer;
// 	char	*line_read;
// 	char	*temp;

// 	line_read = ft_strdup("");
// 	if (!line_read)
// 		return (NULL);
// 	while (1)
// 	{
// 		single_buffer = read_single_buffer(fd);
// 		if (single_buffer == NULL)
// 		{
// 			if (ft_strlen(line_read) > 0)
// 				return (line_read);
// 			free(line_read);
// 			return (NULL);
// 		}
// 		temp = ft_strjoin(line_read, single_buffer);
// 		free(line_read);
// 		free(single_buffer);
// 		if (!temp)
// 			return (NULL);
// 		line_read = temp;
// 		if (ft_strchr(line_read, '\n') != NULL)
// 			return (line_read);
// 	}
// 	return (line_read);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*saved_chars;
// 	char		*line_read;
// 	char		*polished_new_line;
// 	char		*new_saved_chars;
// 	char		*temp_polished_line;

// 	if (!saved_chars)
// 		saved_chars = NULL;
// 	if (saved_chars != NULL)
// 	{
// 		temp_polished_line = saved_chars;
// 		if (ft_strchr(saved_chars, '\n') != NULL)
// 		{
// 			polished_new_line = polish_new_line(saved_chars);
// 			if (!polished_new_line)
// 				return (NULL);
// 			new_saved_chars = create_saved_chars(saved_chars);
// 			free(saved_chars);
// 			saved_chars = new_saved_chars;
// 			return (polished_new_line);
// 		}
// 	}
// 	line_read = return_single_line(fd);
// 	if (line_read == NULL)
// 	{
// 		if (saved_chars != NULL)
// 		{
// 			polished_new_line = polish_new_line(saved_chars);
// 			free(saved_chars);
// 			saved_chars = NULL;
// 			return (polished_new_line);
// 		}
// 		return (NULL);
// 	}
// 	if (saved_chars)
// 	{
// 		temp_polished_line = (char *)ft_calloc(ft_strlen(saved_chars) + 1,
// 				sizeof(char));
// 		if (temp_polished_line == NULL)
// 			return (NULL);
// 		ft_memmove(temp_polished_line, saved_chars, ft_strlen(saved_chars));
// 	}
// 	new_saved_chars = create_saved_chars(line_read);
// 	free(saved_chars);
// 	saved_chars = new_saved_chars;
// 	polished_new_line = polish_new_line(line_read);
// 	free(line_read);
// 	if (temp_polished_line != NULL)
// 	{
// 		return (ft_strjoin(temp_polished_line, polished_new_line));
// 	}
// 	else
// 	{
// 		return (polished_new_line);
// 	}
// }

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

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
