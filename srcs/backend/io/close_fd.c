/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pfd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:10:31 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 10:16:54 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

void	close_fd(t_icmd *cmds)
{
	int	i;

	i = -1;
	while (cmds[i])
	{
		close(cmds[i].pipe[0]);
		close(cmds[i].pipe[1]);
		if (cmds[i].fd_in != 0)
			close(cmds[i].fd_in);
		if (cmds[i].fd_out != 0)
			close(cmds[i].fd_out);
	}
}
