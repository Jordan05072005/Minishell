/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:39:04 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/29 15:54:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	set_io_cp(int child, int nb_cmds, t_icmd *cmds)
{
	if (cmds[child].here_doc)
	{
		here_doc(cmds[child], cmds, nb_cmds);
	}
	else if (cmds[child].fd_in != 0)
	{
		if (dup2(cmds[child].fd_in, 0) == -1)
			ft_perror(1, clean_icmds(cmds, nb_cmds), "File does not exist\n");
	}
	else if (child > 0)
	{
		if (dup2(cmds[child].pipe[0], 0) == -1)
			ft_perror(1, clean_icmds(cmds, nb_cmds), "File does not exist\n");
	}
	if (cmds[child].fd_out != 1)
	{
		if (dup2(cmds[child].fd_out, 1) == -1)
			ft_perror(1, clean_icmds(cmds, nb_cmds), "File does not exist\n");
	}
	else if (child < nb_cmds - 1)
	{
		if (dup2(cmds[child + 1].pipe[1], 1) == -1)
			ft_perror(1, clean_icmds(cmds, nb_cmds), "File does not exist\n");
	}
}
