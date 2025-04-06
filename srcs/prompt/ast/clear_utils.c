/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:20:16 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/06 13:13:11 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	clear_blocks(t_list *cmds)
{
	t_list	*next;

	while (cmds)
	{
		clean_pars((t_pars *)cmds->content);
		next = cmds->next;
		ft_del2((void **)&cmds);
		cmds = next;
		if (cmds)
		{
			ft_del2((void **)&cmds->content);
			next = cmds->next;
			ft_del2((void **)&cmds);
			cmds = next;
		}
	}
}
