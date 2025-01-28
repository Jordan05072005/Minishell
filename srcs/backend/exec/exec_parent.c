/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:21:07 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 10:49:51 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

int	exec_parent(t_icmd *cmds, int nb_cmds)
{
	pid_t	wpid;
	int		child;
	int		status;
	int		exit_code;

	close_fd(cmds);
	child = nb_cmds;
	exit_code = 1;
	while (--child >= 0)
	{
		wpid = waitpid(cmds[child].pid, &status, 0);
		if (wpid == cmds[nb_cmds - 1].pid)
			if ((child == (nb_cmds - 1)) && WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
	}
	// ft_del(data->p_fd);
	// ft_del(data->f_id);
	// if (data->fd_out == -1)
	// 	exit_code = 1;
	return (exit_code);
}