/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_gnl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:40:23 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/26 15:17:02 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// char	*gnl(int fd, int buffsize)
// {
// 	char	*buffer;
// 	ssize_t	bytes_read;
// 	size_t	i;

// 	buffer = malloc(buff_size * sizeof(char));
// 	if (!buffer)
// 		return (NULL);
// 	i = 0;
// 	while (1)
// 	{
// 		bytes_read = read(fd, &buffer[i], buff_size);
// 		if (bytes_read <= 0)
// 		{
// 			if (i == 0 || bytes_read < 0)
// 				return (free(buffer), NULL);
// 			continue ;
// 		}
// 		if (buffer[bytes_read + i - 1] == '\n')
// 			break ;
// 		i += bytes_read;
// 		if (i >= buff_size - 1) 
// 		{
// 			buff_size += buff_size;
// 			buffer = ft_realloc(buffer, buff_size * sizeof(char));
// 			if (!buffer)
// 				return (NULL);
// 		}
// 	}
// 	buffer[bytes_read + i] = 0;
// 	return (buffer);
// }

char	*custom_gnl(int fd)
{
	char	*buffer;
	ssize_t	bytes_read;
	size_t	i;
	size_t	buff_size;

	buff_size = 1024;
	buffer = malloc(buff_size * sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	while (1)
	{
		bytes_read = read(fd, &buffer[i], buff_size);
		if (bytes_read <= 0)
		{
			if (i == 0 || bytes_read < 0)
				return (free(buffer), NULL);
			continue ;
		}
		if (buffer[bytes_read + i - 1] == '\n')
			break ;
		i += bytes_read;
		if (i >= buff_size - 1) 
		{
			buff_size += buff_size;
			buffer = ft_realloc(buffer, buff_size * sizeof(char));
			if (!buffer)
				return (NULL);
		}
	}
	buffer[bytes_read + i] = 0;
	return (buffer);
}
