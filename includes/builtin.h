/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:32:57 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/27 17:17:19 by hle-hena         ###   ########.fr       */
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
char	*check_curpath(char *curpath, char *arg);
char	*clean_curpath(char *curpath);
char	*get_curpath(char *arg, int *print);
//cd_env.c
void	update_env(char *curpath);
//utils.c
char	*create_path(char *first_component, char *second_component);
char	*test_cdpath(char **cdpath, char *arg);
int		is_dot(char *path);

int		ft_color(char **av);

#endif