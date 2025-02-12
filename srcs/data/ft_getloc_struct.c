/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getloc_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:28:05 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/04 13:28:05 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_list	*ft_getloc_struct(const char *str, t_list **placeholder)
{
	int		size;
	char	*line;
	t_list	*loc;

	size = ft_strlen(str);
	loc = data()->loc;
	*placeholder = NULL;
	while (loc)
	{
		line = ft_strnstr(loc->content, str, size);
		if (line && line[size] == '=')
		{
			if (loc == data()->loc)
				*placeholder = NULL;
			else
				*placeholder = loc;
			return (loc);
		}
		loc = loc->next;
	}
	return (NULL);
}
