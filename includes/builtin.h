/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:32:57 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/10 18:05:55 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <sys/stat.h>

int		ft_exit(char **av);

int		ft_pwd(char **arg);

int		ft_unset(char **arg);

int		ft_env(char **arg);

int		ft_echo(t_icmd *cmd);

int		ft_export(char **arg);
int		export_var(char *str);

int		ft_cd(char **av);
//curpath.c
char	*check_curpath(char *curpath, char *arg, int special_print);
char	*clean_curpath(char *curpath);
char	*get_curpath(char *arg, int *print);
char	*cd_error_messages(char *curpath, char *arg, int special_print);
//cd_env.c
void	update_env(char *curpath);
//utils.c
char	*create_path(char *first_component, char *second_component);
char	*test_cdpath(char **cdpath, char *arg);
int		is_dot(char *path);

int		ft_color(char **av);

#endif