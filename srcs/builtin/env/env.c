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

#include "env.h"

int	ft_env(char **arg)
{
	t_list	*env;

	env = data()->env;
	while (env)
	{
		ft_printf("%s", env->content);
		env = env->next;
	}
}