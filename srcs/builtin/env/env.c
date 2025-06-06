/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:12:19 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/04 14:12:19 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_env(char **arg)
{
	t_list	*env;

	if (ft_strslen(arg) > 1)
		return (ft_perror(-1, ft_strdup("mini: env: Only one argument."), 0),
			1);
	env = data()->env;
	printf("%s\n", (char *)env->content);
	while (env->next)
	{
		env = env->next;
		if (!ft_strchr(env->content, '='))
			continue ;
		printf("%s\n", (char *)env->content);
	}
	return (0);
}
