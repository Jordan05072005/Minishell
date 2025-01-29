/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:35:06 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/29 10:49:51 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	exec(int nb_cmds, t_cmd *input, char **env)
{
	int	pid;
	int	status;
	int	exit_code;

	pid = fork();
	if (pid == -1)
		ft_perror(1, 0, "A subprocess was not started.");
	if (pid == 0)
		exec_proc(env, input, nb_cmds);
	exit_code = 1;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	ft_printf("\n\n\nExit status is %d\n", exit_code);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_cmd	input[2];
	char	*args1[] = {"ls", "-a", "-R", NULL};
	char	*args2[] = {"cat", "-e", NULL};

	input[0].in = "Makefile";
	input[0].out = NULL;
	input[0].here_doc = NULL;
	input[0].args = args1;
	input[0].append = 0;
	input[1].in = "Makefile";
	input[1].out = "test";
	input[1].here_doc = "EOF";
	input[1].args = args2;
	input[1].append = 1;
	exec(2, input, env);
	(void) ac;
	(void) av;
}