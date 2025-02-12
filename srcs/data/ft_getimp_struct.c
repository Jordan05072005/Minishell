/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getimp_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:09:42 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/12 17:31:14 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_list	*ft_getimp_struct(const char *str, t_list **placeholder)
{
	int		size;
	char	*line;
	t_list	*imp;

	size = ft_strlen(str);
	imp = data()->imp;
	*placeholder = NULL;
	while (imp)
	{
		line = ft_strnstr(imp->content, str, size);
		if (line && line[size] == '=')
		{
			if (imp == data()->imp)
				*placeholder = NULL;
			else
				*placeholder = imp;
			return (imp);
		}
		imp = imp->next;
	}
	return (NULL);
}
