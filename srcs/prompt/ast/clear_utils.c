/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:20:16 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/08 13:18:32 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	clear_blocks(t_list *cmds)
{
	t_list	*next;

	if (!cmds)
		return ;
	while (cmds)
	{
		ft_del2((void **)&cmds->content);
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

void	clear_tree(t_bt *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		clear_tree(tree->left);
	if (tree->right)
		clear_tree(tree->right);
	ft_del2((void **)&tree->content);
	ft_del2((void **)&tree);
}

void	del_unusedlst(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		ft_del2((void **)&lst);
		lst = next;
	}
}
