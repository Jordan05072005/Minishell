/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:50:49 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/04 14:41:54 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ft_getenv(const char *str)
{
	int		size;
	char	*line;
	t_list	*env;

	size = ft_strlen(str);
	env = data()->env;
	if (!env)
		return (NULL);
	line = ft_strnstr(env->content, str, size);
	while (!line && env->next)
	{
		env = env->next;
		line = ft_strnstr(env->content, str, size);
	}
	if (!line)
		return (NULL);
	return (line + size + 1);
}
