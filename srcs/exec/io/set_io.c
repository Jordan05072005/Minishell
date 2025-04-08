/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:39:04 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/07 10:16:30 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	set_io_p(int child, int nb_cmds, t_icmd *cmds)
{
	if (cmds[child].here_doc)
		here_doc(cmds[child]);
	else if (cmds[child].fd_in != 0)
	{
		if (dup2(cmds[child].fd_in, 0) == -1)
			return (ft_perror(-1, NULL, 0), 1);
	}
	else if (child > 0)
	{
		if (dup2(cmds[child].pipe[0], 0) == -1)
			return (ft_perror(-1, ft_strdup("mini: Internal error: Broken pipe.\
"), 0), 1);
	}
	if (cmds[child].fd_out != 1)
	{
		if (dup2(cmds[child].fd_out, 1) == -1)
			return (ft_perror(-1, NULL, 0), 1);
	}
	else if (child < nb_cmds - 1)
	{
		if (dup2(cmds[child + 1].pipe[1], 1) == -1)
			return (ft_perror(-1, ft_strdup("mini: Internal error: Broken pipe.\
"), 0), 1);
	}
	return (0);
}

void	set_io_cp(int child, int nb_cmds, t_icmd *cmds)
{
	if (cmds[child].here_doc)
		here_doc(cmds[child]);
	else if (cmds[child].fd_in != 0)
	{
		if (dup2(cmds[child].fd_in, 0) == -1)
			ft_perror(1, NULL, clean_data() + clean_icmds());
	}
	else if (child > 0)
	{
		if (dup2(cmds[child].pipe[0], 0) == -1)
			ft_perror(1, ft_strdup("mini: Internal error: Broken pipe."),
				clean_data() + clean_icmds());
	}
	if (cmds[child].fd_out != 1)
	{
		if (dup2(cmds[child].fd_out, 1) == -1)
			ft_perror(1, NULL, clean_data() + clean_icmds());
	}
	else if (child < nb_cmds - 1)
	{
		if (dup2(cmds[child + 1].pipe[1], 1) == -1)
			ft_perror(1, ft_strdup("mini: Internal error: Broken pipe."),
				clean_data() + clean_icmds());
	}
}
