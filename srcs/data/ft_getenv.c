/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:50:49 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/12 18:16:59 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_getenv(const char *str)
{
	int		size;
	char	*line;
	t_list	*env;

	size = ft_strlen(str);
	env = data()->env;
	while (env)
	{
		line = ft_strnstr(env->content, str, size);
		if (line && line[size] == '=')
			return (line + size + 1);
		env = env->next;
	}
	return (NULL);
}
