/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:02:01 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/05 12:58:13 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	here_doc(t_icmd cmd, t_icmd *cmds, int nb_cmds)
{
	int		p_fd[2];
	pid_t	f_id;
	char	*temp;

	if (pipe(p_fd) == -1)
		ft_perror(1, clean_icmds(cmds, nb_cmds), "A pipe didn't open.");
	f_id = fork();
	if (f_id == -1)
		ft_perror(1, clean_icmds(cmds, nb_cmds), "A subprocess was not \
started.");
	if (f_id == 0)
	{
		close(p_fd[0]);
		while (1)
		{
			temp = get_next_line(0);
			if (ft_strncmp(temp, cmd.here_doc, ft_strlen(cmd.here_doc)) == 0
				&& temp[ft_strlen(cmd.here_doc)] == 0)
				return (ft_del(temp), exit(0));
			ft_putstr_fd(temp, p_fd[1]);
			ft_del(temp);
		}
	}
	close(p_fd[1]);
	dup2(p_fd[0], 0);
}
