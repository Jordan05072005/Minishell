/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_icmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:50:49 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/21 14:15:16 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_icmd	*init_icmds(t_cmd *input, int nb_cmds)
{
	t_icmd	*cmds;
	int		i;

	data()->cmds = ft_calloc(nb_cmds + 1, sizeof(t_icmd));
	cmds = data()->cmds;
	data()->nb_cmds = nb_cmds;
	if (!cmds)
		ft_perror(1, ft_strdup("mini: Internal error: malloc"), clean_data());
	zero_out(cmds, nb_cmds);
	i = -1;
	while (++i < nb_cmds)
		init_icmd(&cmds[i], input[i]);
	return (cmds);
}
