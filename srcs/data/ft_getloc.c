/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:51:51 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/03 08:54:13 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "emv.h"

char	*ft_getloc(const char *str)
{
	int		i;
	int		size;
	char	*line;
	t_list	loc;

	i = 0;
	size = ft_strlen(str);
	loc = data()->loc;
	line = ft_strnstr(loc.content, str, size);
	while (!line && loc->next)
	{
		loc = loc->next;
		line = ft_strnstr(loc.content, str, size);
	}
	if (!line)
		return (NULL);
	return (line + size);
}
