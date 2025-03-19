/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:20:16 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/19 13:54:22 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	clear_blocks(t_list *cmds)
{
	t_list	*next;

	while (cmds)
	{
		clean_pars((t_pars *)cmds->content);
		// clear_pipeline((t_list *)cmds->content);
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
