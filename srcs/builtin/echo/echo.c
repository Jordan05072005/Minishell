/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:33:22 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/05 19:33:22 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_echo(t_icmd *cmd)
{
	int	i;

	if (cmd->fd_in)
		return (0);
	i = 0;
	if (cmd->args[1] && !ft_strncmp(cmd->args[1], "-n", 3))
		i = 1;
	while (cmd->args[1] && cmd->args[++i])
		ft_putstr_fd(ft_strtrim(cmd->args[i], "\""), cmd->fd_out);
	if (!cmd->args[1] || ft_strncmp(cmd->args[1], "-n", 3) != 0)
		write(cmd->fd_out, "\n", 1);
	return (1);
}