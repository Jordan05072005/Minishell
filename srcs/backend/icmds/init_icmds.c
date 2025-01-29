/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_icmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:50:49 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/29 12:50:12 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

t_icmd	*init_icmds(t_cmd *input, int nb_cmds)
{
	t_icmd	*cmds;
	int		i;

	cmds = ft_calloc(nb_cmds + 1, sizeof(t_icmd));
	if (!cmds)
		ft_perror(1, clean_icmds(cmds, nb_cmds), "An error occured during the \
malloc of the structure\n");
	zero_out(cmds, nb_cmds);
	i = -1;
	while (++i < nb_cmds)
		init_icmd(&cmds[i], input[i], nb_cmds);
	return (cmds);
}
