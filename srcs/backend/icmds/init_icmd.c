/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_icmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:01:55 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 11:13:17 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

void	init_icmd(t_icmd *cmd, t_cmd input)
{
	if (input.in && !input.here_doc)
		cmds->fd_in = open(input.in, O_RDONLY, 0777);
	if (input.out && !append_out)
		cmds->fd_out = open(input.out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (input.out && append_out)
		cmds->fd_out = open(input.out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	// cmds->here_doc = input.here_doc;
	//Should read here for here_doc
	cmds->path = get_path(input.args[0]);
	cmds->args = input.args;
}
