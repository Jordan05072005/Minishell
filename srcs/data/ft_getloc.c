/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:51:51 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/05 12:57:34 by hle-hena         ###   ########.fr       */
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
	if (!loc)
		return (NULL);
	line = ft_strnstr(loc->content, str, size);
	while (!line && loc->next)
	{
		loc = loc->next;
		line = ft_strnstr(loc->content, str, size);
	}
	if (!line)
		return (NULL);
	return (line + size);
}
