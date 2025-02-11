/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:10:31 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/11 17:01:38 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	close_fd(t_icmd *cmds, int nb_cmds, int child)
{
    int i;

    i = -1;
    while (++i < nb_cmds)
    {
        if (i != child + 1) // Don't close the next child's read pipe
            close(cmds[i].pipe[0]);

        if (i != child) // Don't close this child's write pipe
            close(cmds[i].pipe[1]);

        if (cmds[i].fd_in > 0)
            close(cmds[i].fd_in);
        if (cmds[i].fd_out > 1)
            close(cmds[i].fd_out);
    }
}
