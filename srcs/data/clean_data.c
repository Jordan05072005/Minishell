/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:42:48 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/05 12:57:02 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	clean_env(void)
{
	t_list	*env;
	t_list	*loc;
	
	env = data()->env;
	loc = data()->loc;
	ft_lstclear(&env, ft_del);
	ft_lstclear(&loc, ft_del);
	return (0);
}

int	clean_pars(void)
{
	t_pars	*cmd;
	
	cmd = data()->cmd;
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
	ft_free_tab((void *)cmd->split, ft_strslen(cmd->split));
	ft_del(cmd->line);
	ft_del(cmd->cmd);
	ft_del(cmd);
	return (0);
}

int	clean_data(void)
{
	clean_env();
	clean_pars();
	return (0);
}
