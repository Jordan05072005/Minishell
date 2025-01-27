/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:39:04 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/27 18:07:12 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

int	set_in(int child, int nb_cmds, t_icmd cmd, t_icmd prev)
{
	if (child == 0)
		if (dup2(cmd.fd_in, 0) == -1)
			exit(1) //should clean things I think ?
	else if (fd_in != 0)
		if (dup2(cmd.fd_in, 0) == -1)
			exit(1) //should clean things I think ?
	else
		if (dup2(prev.pipe[0], 0) == -1)
			exit(1) //should clean things I think ?
	if (child ==)
}
