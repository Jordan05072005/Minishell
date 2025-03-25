/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:42:48 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/25 16:59:36 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	clean_env(void)
{
	ft_lstclear(&(data()->env), ft_del);
	ft_lstclear(&(data()->loc), ft_del);
	ft_lstclear(&(data()->imp), ft_del);
	return (0);
}

int	clean_pars(t_pars *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->exe)
	{
		while (--cmd->pipe >= 0)
		{
			ft_free_tab((void **)cmd->exe[cmd->pipe].args,
				ft_strslen(cmd->exe[cmd->pipe].args));
		}
		ft_free_tab((void *)(cmd->exe[0].split),
			ft_strslen(cmd->exe[0].split));
		ft_del(cmd->exe);
	}
	// ft_del(cmd->line);
	ft_del(cmd->cmd);
	ft_del(cmd);
	data()->cmd = NULL;
	return (0);
}

int	clean_data(void)
{
	clean_env();
	return (0);
}
