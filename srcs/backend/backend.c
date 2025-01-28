/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:35:06 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 10:55:03 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	exec(int nb_cmds, t_cmd *input, char **env)
{
	t_icmd	*cmds;

	if (nb_cmds == 0)
		return (0);
	cmds = init_icmds(env, input, nb_cmds);
}
