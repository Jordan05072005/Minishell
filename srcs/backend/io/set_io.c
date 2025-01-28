/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:39:04 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 19:15:06 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

void	set_io_cp(int child, int nb_cmds, t_icmd *cmds)
{
	if (cmds[child].here_doc)
	{
		here_doc(cmds[child]);
	}
	else if (child == 0 || cmds[child].fd_in != 0)
	{
		if (dup2(cmds[child].fd_in, 0) == -1)
			exit(1); //should clean things I think ?
	}
	else
	{
		if (dup2(cmds[child - 1].pipe[0], 0) == -1)
			exit(1); //should clean things I think ?
	}
	if (child == nb_cmds - 1 || cmds[child].fd_out != 0)
	{
		if (dup2(cmds[child].fd_out, 1) == -1)
			exit(1); //should clean things I think ?
	}
	else
	{
		if (dup2(cmds[child + 1].pipe[1], 1) == -1)
			exit(1); //should clean things I think ?
	}
}
