/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:51:51 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/12 15:55:45 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	print_list(void *content)
{
	ft_printf("[%s] - ", content);
}

char	*ft_getloc(const char *str)
{
	int		size;
	char	*line;
	t_list	*loc;

	size = ft_strlen(str);
	loc = data()->loc;
	// ft_lstiter(data()->loc, print_list);
	// ft_printf("\n");
	if (!loc)
		return (NULL);
	while (loc)
	{
		line = ft_strnstr(loc->content, str, size);
		if (line && line[size] == '=')
			return (line + size + 1);
		loc = loc->next;
	}
	return (NULL);
}
