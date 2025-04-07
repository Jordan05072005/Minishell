/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:27:19 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/07 10:55:31 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <wait.h>

int		exec(int nb_cmds, t_cmd *input);
t_icmd	*init_icmds(t_cmd *input, int nb_cmds);
void	init_icmd(t_icmd *cmd, t_cmd input);
char	*get_path(t_cmd input, t_icmd *cmd);
void	exec_child(t_icmd *cmds, int nb_cmds, int child);
void	set_io_cp(int child, int nb_cmds, t_icmd *cmds);
void	here_doc(t_icmd cmd);
void	close_fd(t_icmd *cmds, int nb_cmds, int child);
int		exec_parent(t_icmd *cmds, int nb_cmds);
int		clean_icmds(void);
int		is_builtin(const char *str);
void	exec_builtin(t_icmd *cmds, int nb_cmds, int child);
void	exec_define(t_icmd *cmds, int nb_cmds, int child);
void	define2child(t_icmd *cmds, int nb_cmds, int child, int start);
int		is_define(char *str);
void	set_exit_val(int ret_val);
char	*custom_gnl(void);
void	exec_subshell(t_icmd *cmds, int child);
void	sigint_here_doc(int sig);
t_list	**get_input_lst(void);
int		set_io_p(int child, int nb_cmds, t_icmd *cmds);

#endif