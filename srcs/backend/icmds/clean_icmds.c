/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_icmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:11:38 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/29 12:50:08 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

int	clean_icmds(t_icmd *cmds, int nb_cmds)
{
	int	child;

	child = -1;
	while (++child < nb_cmds)
		ft_del(cmds[child].path);
	ft_del(cmds);
	return (0);
}
