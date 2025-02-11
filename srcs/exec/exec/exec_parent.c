/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:21:07 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/11 17:31:41 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	exec_parent(t_icmd *cmds, int nb_cmds)
{
	pid_t	wpid;
	int		child;
	int		status;
	int		exit_code;

	close_fd(cmds, nb_cmds, -2);
	child = nb_cmds;
	exit_code = 1;
	while (--child >= 0)
	{
		if (cmds[child].exit != -1 && nb_cmds == 1)
		{
			if (child == nb_cmds - 1)
				exit_code = cmds[child].exit;
			continue ;
		}
		wpid = waitpid(cmds[child].pid, &status, 0);
		if (wpid == cmds[nb_cmds - 1].pid)
			if ((child == (nb_cmds - 1)) && WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
	}
	clean_icmds(cmds, nb_cmds);
	return (exit_code);
}
