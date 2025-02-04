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

#include "env.h"

t_list	*ft_getloc_struct(const char *str)
{
	int		i;
	int		size;
	char	*line;
	t_list	*loc;

	i = 0;
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
	return (loc);
}