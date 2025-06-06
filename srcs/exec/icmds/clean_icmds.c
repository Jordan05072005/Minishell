/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_icmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:11:38 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/28 15:43:38 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	clean_icmds(void)
{
	t_icmd	*cmds;
	int		nb_cmds;
	int		child;

	cmds = data()->cmds;
	nb_cmds = data()->nb_cmds;
	child = -1;
	while (++child < nb_cmds)
	{
		ft_del(cmds[child].path);
		if (cmds->type == -1)
			ft_del(cmds[child].args);
	}
	ft_del(cmds);
	return (0);
}
