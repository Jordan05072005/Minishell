/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:50:49 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/04 13:50:53 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ft_getenv(const char *str)
{
	int		i;
	int		size;
	char	*line;
	t_list	*env;

	i = 0;
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
	return (line + size);
}
