/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:47:25 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/03 10:49:05 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_list	*ft_getenv_struct(const char *str)
{
	int		i;
	int		size;
	char	*line;
	t_list	env;

	i = 0;
	size = ft_strlen(str);
	env = data()->env;
	line = ft_strnstr(env.content, str, size);
	while (!line && env->next)
	{
		env = env->next;
		line = ft_strnstr(env.content, str, size);
	}
	if (!line)
		return (NULL);
	return (&env);
}
