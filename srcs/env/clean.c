/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:42:48 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/03 16:24:01 by jguaglio         ###   ########.fr       */
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

// void	ft_lstclear(t_var **lst)
// {
// 	t_var	*temp;

// 	while (*lst)
// 	{
// 		temp = (*lst)->next;
// 		if (del)
// 			ft_free_tab((*lst)->split, ft_strstrlen((*lst)->split));
// 		free(*lst);
// 		*lst = temp;
// 	}
// 	*lst = 0;
// }

// int	clean_temp(t_data *d)
// {
// 	while (--d->cmd->pipe >= 0)
// 	{
// 		ft_free_tab((void *)(d->cmd->exe[d->cmd->pipe].split), ft_strstrlen(d->cmd->exe[d->cmd->pipe].split));
// 		ft_free_tab((void **)d->cmd->exe[d->cmd->pipe].args, ft_strstrlen(d->cmd->exe[d->cmd->pipe].args));
// 		ft_del(d->cmd->exe);
// 	}
// 	ft_free_tab((void *)d->cmd->split, ft_strstrlen(d->cmd->split));
// 	ft_del(d->cmd->line);
// 	ft_del(d->cmd->cmd);
// 	ft_del(d->cmd);
// 	ft_lstclear(d->var);
// 	return (0);
// }