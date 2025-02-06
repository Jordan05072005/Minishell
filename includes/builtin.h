/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:32:57 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/05 19:59:29 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <sys/stat.h>

int		ft_exit(void);
int		ft_pwd(char **arg);
int		ft_cd(char **av);
int		ft_unset(char **arg);
int		ft_env(char **arg);
int	ft_echo(t_icmd *cmd);
char	*create_path(char *first_component, char *second_component);

#endif