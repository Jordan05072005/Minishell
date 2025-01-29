/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:35:06 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/29 14:18:35 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	exec(int nb_cmds, t_cmd *input, char **env)
{
	//Is using the wrong env
	t_icmd	*cmds;
	int		child;

	cmds = init_icmds(input, nb_cmds);
	child = -1;
	while (++child < nb_cmds)
	{
		if (!is_builtin(cmds[child].args[0]))
		{
			cmds[child].pid = fork();
			if (cmds[child].pid == -1)
				ft_perror(1, clean_icmds(cmds, nb_cmds), "A subprocess was not \
started.");
			if (cmds[child].pid == 0)
				exec_child(cmds, nb_cmds, child, env);
		}
		else
			exec_builtin(cmds, nb_cmds, child, env);
	}
	return (exec_parent(cmds, nb_cmds));
}

int	main(int ac, char **av, char **env)
{
	t_cmd	input[2];
	char	*args1[] = {"./../../../fdf/fdf", "../../../fdf/maps/t1.fdf", NULL};
	char	*args2[] = {"grep", "fps", NULL};

	input[0].in = NULL;
	input[0].out = NULL;
	input[0].here_doc = NULL;
	input[0].args = args1;
	input[0].append = 0;
	input[1].in = NULL;
	input[1].out = NULL;
	input[1].here_doc = NULL;
	input[1].args = args2;
	input[1].append = 1;
	ft_printf("\n\n\nExit code is %d\n", exec(1, input, env));
	(void) ac;
	(void) av;
}
