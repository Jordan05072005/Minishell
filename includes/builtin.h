/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:32:57 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/14 12:02:13 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <sys/stat.h>

int		ft_exit(void);

int		ft_pwd(char **arg);

int		ft_unset(char **arg);

int		ft_env(char **arg);

int		ft_echo(t_icmd *cmd);

int	ft_export(char **arg);

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
char	*ft_delcot(char *str, int i);

int		ft_color(char **av);

#endif