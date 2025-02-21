/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:02:01 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/21 14:12:48 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	here_doc(t_icmd cmd)
{
	int		p_fd[2];
	pid_t	f_id;
	char	*temp;

	if (pipe(p_fd) == -1)
		ft_perror(1, ft_strdup("mini: Internal error: pipe."), clean_icmds() + clean_data());
	f_id = fork();
	if (f_id == -1)
		ft_perror(1, ft_strdup("mini: Internal error: process."), clean_icmds() + clean_data());
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
