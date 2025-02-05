/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:27:19 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/05 13:07:27 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <wait.h>
# include "struct.h"

int		exec(int nb_cmds, t_cmd *input);
t_icmd	*init_icmds(t_cmd *input, int nb_cmds);
void	zero_out(t_icmd *cmds, int nb_cmds);
void	init_icmd(t_icmd *cmd, t_cmd input, int nb_cmds);
char	*get_path(t_cmd cmd, t_icmd *cmds, int nb_cmds);
void	exec_child(t_icmd *cmds, int nb_cmds, int child);
void	set_io_cp(int child, int nb_cmds, t_icmd *cmds);
void	here_doc(t_icmd cmd, t_icmd *cmds, int nb_cmds);
void	close_fd(t_icmd *cmds, int nb_cmds);
int		exec_parent(t_icmd *cmds, int nb_cmds);
int		clean_icmds(t_icmd *cmds, int nb_cmds);
int		is_builtin(const char *str);
void	exec_builtin(t_icmd *cmds, int nb_cmds, int child);

#endif