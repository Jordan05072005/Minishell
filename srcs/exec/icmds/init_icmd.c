/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_icmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:01:55 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/26 16:00:06 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	init_icmd(t_icmd *cmd, t_cmd input)
{
	if (input.in && !input.here_doc)
		cmd->fd_in = open(input.in, O_RDONLY, 0777);
	if (input.out && !input.append)
		cmd->fd_out = open(input.out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (input.out && input.append)
		cmd->fd_out = open(input.out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	cmd->define = 0;
	cmd->here_doc = input.here_doc;
	cmd->args = input.args;
	cmd->path = get_path(input, cmd);
	if (pipe(cmd->pipe) == -1)
		return (ft_perror(1, ft_strdup("mini: Internal error: pipe."),
			clean_icmds() + clean_data()));
}
