/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.fr>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-05 14:59:21 by hle-hena          #+#    #+#             */
/*   Updated: 2025-03-05 14:59:21 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_bt	*ft_btnew(void *content)
{
	t_bt	*node;

	node = ft_calloc(1, sizeof(t_bt));
	if (!node)
		return (NULL);
	node->content = content;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_bt	*create_bt_node(void *content)
{
	t_bt	*node;

	if (!content)
		ft_perror(1, ft_strdup("mini: Internal error: malloc."), clean_data());
	node = ft_btnew(content);
	if (!node)
	{
		ft_del((void **)&content);
		ft_perror(1, ft_strdup("mini: Internal error: malloc."), clean_data());
	}
	return (node);
}

void	set_parent(t_bt *parent, t_bt *child, int right)
{
	if (parent)
	{
		if (right)
			parent->right = child;
		else
			parent->left = child;
		child->parent = parent;
	}
}
