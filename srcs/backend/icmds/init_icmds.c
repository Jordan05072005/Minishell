/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_icmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:50:49 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 10:56:47 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

void	init_icmds(char **env, t_cmd *input, int nb_cmds)
{
	t_icmd	*cmds;

	cmds = ft_calloc(nb_cmds + 1, sizeof(t_icmd));
	if (!cmds)
		exit(1); //should clean ig
	return (cmds);
}