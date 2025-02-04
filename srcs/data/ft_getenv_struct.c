/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:47:25 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/04 14:32:27 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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
