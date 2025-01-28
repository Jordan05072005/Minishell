/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:35:06 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 19:18:52 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	exec(int nb_cmds, t_cmd *input, char **env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_perror(1, 0, "A subprocess was not started.");
	if (pid == 0)
		exec_proc(env, input, nb_cmds);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_cmd	input1;
	char	 *args1[] = {"cat", "-e", NULL};

	input1.in = "Makefile";
	input1.out = NULL;
	input1.here_doc = "NULL";
	input1.args = args1;
	input1.append = 0;
	exec(1, &input1, env);
	(void) ac;
	(void) av;
}