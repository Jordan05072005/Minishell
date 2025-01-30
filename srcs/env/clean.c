/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:42:48 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/30 16:54:58 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	clean_temp(t_pars *cmd)
{
	while (--cmd->pipe >= 0)
	{
		ft_free_tab((void *)(cmd->exe[cmd->pipe].split), ft_strstrlen(cmd->exe[cmd->pipe].split));
		ft_free_tab((void **)cmd->exe[cmd->pipe].args, ft_strstrlen(cmd->exe[cmd->pipe].args));
		ft_del(cmd->exe);
	}
	ft_free_tab((void *)cmd->split, ft_strstrlen(cmd->split));
	ft_del(cmd->line);
	ft_del(cmd->cmd);
	ft_del(cmd);
	return (0);
}