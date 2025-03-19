/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:20:16 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/19 13:25:43 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	clear_blocks(t_list *cmds)
{
	t_list	*next;

	while (cmds)
	{
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
