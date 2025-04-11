/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_gnl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:40:23 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/11 10:48:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**get_buffer(void)
{
	static char	*buff = NULL;

	return (&buff);
}

char	*get_line(int *b_read, char **buffer, int *i, int buff_size)
{
	while (1)
	{
		*b_read = read(0, &(*buffer)[*i], buff_size);
		if (*b_read <= 0)
		{
			if (*i == 0 || *b_read < 0)
				return (free(*buffer), NULL);
			continue ;
		}
		if ((*buffer)[*b_read + *i - 1] == '\n')
			break ;
		*i += *b_read;
		if (*i >= buff_size - 1)
		{
			buff_size += buff_size;
			*buffer = ft_realloc(*buffer, buff_size * sizeof(char));
			if (!*buffer)
				return (NULL);
		}
	}
	(*buffer)[*b_read + *i] = 0;
	return (*buffer);
}

char	*custom_gnl(void)
{
	char	**buffer;
	int		bytes_read;
	int		i;
	int		buff_size;

	buffer = get_buffer();
	buff_size = 1024;
	*buffer = malloc(buff_size * sizeof(char));
	if (!*buffer)
		return (NULL);
	i = 0;
	bytes_read = 0;
	return (get_line(&bytes_read, buffer, &i, buff_size));
}

void	sigint_here_doc(int sig)
{
	t_list	**lst;

	(void)sig;
	lst = get_input_lst();
	ft_putstr_fd("\n", 1);
	ft_lstclear(lst, ft_del);
	ft_del(*get_buffer());
	(void)(clean_data() + clean_icmds());
	exit(0);
}
