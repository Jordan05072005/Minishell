/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:00:15 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/06 16:03:42 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	exec_subshell(t_icmd *cmds, int child)
{
	char	*sub;
	int		ret;

	cmds[child].pid = fork();
	if (cmds[child].pid == -1)
		ft_perror(1, ft_strdup("mini: Internal error: process."),
			clean_data() + clean_icmds());
	if (cmds[child].pid == 0)
	{
		sub = ft_strdup(cmds[child].args[0]);
		clear_tree(data()->ast);
		clean_icmds();
		data()->ast = get_ast(sub);
		ft_del(sub);
		run_ast(data()->ast);
		ret = ft_atoi(ft_getimp("?"));
		clean_data();
		exit(ret);
	}
}
