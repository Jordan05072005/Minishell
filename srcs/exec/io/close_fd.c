/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:10:31 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/29 15:54:27 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_fd(t_icmd *cmds, int nb_cmds)
{
	int	i;

	i = -1;
	while (++i < nb_cmds)
	{
		close(cmds[i].pipe[0]);
		close(cmds[i].pipe[1]);
		if (cmds[i].fd_in > 0)
			close(cmds[i].fd_in);
		if (cmds[i].fd_out > 1)
			close(cmds[i].fd_out);
	}
}
