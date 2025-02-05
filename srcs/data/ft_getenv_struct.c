/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:47:25 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/05 12:57:24 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_list	*ft_getenv_struct(const char *str)
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
	return (env);
}
