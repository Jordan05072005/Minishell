/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_icmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:57:07 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 11:11:43 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

void	zero_out(t_icmd *cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
	{
		cmds[i].fd_in = 0;
		cmds[i].fd_out = 1;
		cmds[i].here_doc = NULL;
		cmds[i].path = NULL;
		cmds[i].args = NULL;
		cmds[i].pipe[0] = 0;
		cmds[i].pipe[0] = 0;
		cmds[i].pid = 0;
	}
}
