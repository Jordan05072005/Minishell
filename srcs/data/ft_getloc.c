/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:51:51 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/26 13:49:47 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_getloc(const char *str)
{
	int		size;
	char	*line;
	t_list	*loc;

	size = ft_strlen(str);
	loc = data()->loc;
	while (loc)
	{
		line = ft_strnstr(loc->content, str, size);
		if (line && line[size] == '=')
		{
			if (line[size + 1])
				return (line + size + 1);
			return (NULL);
		}
		loc = loc->next;
	}
	return (NULL);
}
