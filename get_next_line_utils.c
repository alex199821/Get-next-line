/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:58:57 by macbook           #+#    #+#             */
/*   Updated: 2024/10/19 08:31:59 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// size_t	ft_strlen(const char *c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (c[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// void	*ft_memset(void *s, int c, size_t n)
// {
// 	unsigned char	*ptr;

// 	ptr = (unsigned char *)s;
// 	while (n--)
// 	{
// 		*ptr = (unsigned char)c;
// 		ptr++;
// 	}
// 	return (s);
// }

// void	*ft_calloc(size_t count, size_t size)
// {
// 	char	*array;
// 	size_t	totalsize;

// 	totalsize = count * size;
// 	array = (char *)malloc(totalsize);
// 	if (array == NULL)
// 	{
// 		return (NULL);
// 	}
// 	ft_memset(array, '\0', totalsize);
// 	return (array);
// }

// void	*ft_memmove(void *dst, const void *src, size_t n)
// {
// 	char		*ptr1;
// 	const char	*ptr2;

// 	ptr1 = dst;
// 	ptr2 = src;
// 	if (!dst && !src)
// 		return (NULL);
// 	if (dst < src)
// 	{
// 		while (n--)
// 		{
// 			*ptr1++ = *ptr2++;
// 		}
// 	}
// 	else
// 	{
// 		while (n--)
// 		{
// 			ptr1[n] = ptr2[n];
// 		}
// 	}
// 	return (dst);
// }

// char	*ft_strdup(const char *src)
// {
// 	size_t	i;
// 	char	*array;

// 	i = ft_strlen(src);
// 	array = (char *)ft_calloc(i + 1, sizeof(char));
// 	if (array == NULL)
// 	{
// 		return (NULL);
// 	}
// 	ft_memmove(array, src, i + 1);
// 	return (array);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t i;
// 	char *array;

// 	i = 0;
// 	if (start >= ft_strlen(s))
// 	{
// 		return (ft_strdup(""));
// 	}
// 	if (len > ft_strlen(s) - start)
// 	{
// 		len = ft_strlen(s) - start;
// 	}
// 	array = (char *)malloc(len + 1);
// 	if (array == NULL)
// 	{
// 		return (NULL);
// 	}
// 	while (i < len && s[start + i] != '\0')
// 	{
// 		array[i] = s[i + start];
// 		i++;
// 	}
// 	array[i] = '\0';
// 	return (array);
// }