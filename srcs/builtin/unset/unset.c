/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:23:39 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/04 13:23:39 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_unset(char **arg)
{
	size_t	i;

	i = 0;
	while (arg[++i])
	{
		ft_lstremove_if(&(data()->loc), is_env, ft_del, arg[i]);
		ft_lstremove_if(&(data()->env), is_env, ft_del, arg[i]);
		if (!ft_strncmp(arg[i], "SHLVL", 6))
			ft_lstadd_back(&data()->env, ft_lstnew(ft_strdup("SHLVL=0")));
	}
	return (0);
}
