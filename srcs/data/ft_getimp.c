/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getimp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:06:13 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/13 18:59:47 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_getimp(const char *str)
{
	int		size;
	char	*line;
	t_list	*imp;

	size = ft_strlen(str);
	imp = data()->imp;
	while (imp)
	{
		line = ft_strnstr(imp->content, str, size);
		if (line && line[size] == '=')
		{
			if (line[size + 1])
				return (line + size + 1);
			return ("");
		}
		imp = imp->next;
	}
	return (NULL);
}
