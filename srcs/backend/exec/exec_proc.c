/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:37:50 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 18:55:58 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

void	exec_proc(char **env, t_cmd *input, int nb_cmds)
{
	t_icmd	*cmds;
	int		child;

	cmds = init_icmds(input, nb_cmds);
	child = -1;
	while (++child < nb_cmds)
	{
		cmds[child].pid = fork();
		if (cmds[child].pid == -1)
			ft_perror(1, 0, "A subprocess was not started.");
		if (cmds[child].pid == 0)
			exec_child(cmds, nb_cmds, child, env);
		// clean_func(&data);
	}
	exit(exec_parent(cmds, nb_cmds));
}