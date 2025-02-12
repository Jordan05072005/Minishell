/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:47:25 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/12 17:31:09 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_list	*ft_getenv_struct(const char *str, t_list **placeholder)
{
	int		size;
	char	*line;
	t_list	*env;

	size = ft_strlen(str);
	env = data()->env;
	*placeholder = NULL;
	while (env)
	{
		line = ft_strnstr(env->content, str, size);
		if (line && line[size] == '=')
		{
			if (env == data()->env)
				*placeholder = NULL;
			else
				*placeholder = env;
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}
