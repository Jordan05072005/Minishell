/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:23:39 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/04 13:23:39 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_lstdel_link(t_list **l, void (*del)(void *), void *content)
{
	t_list	*cpy;
	t_list	*temp;

	cpy = *l;
	if (!cpy)
		return ;
	while (cpy->next && cpy->next->content != content)
		cpy = cpy->next;
	if (cpy == NULL || cpy->next == NULL)
		return;
	temp = cpy->next;
	cpy->next = cpy->next->next;
	del(temp);
}

int	ft_unset(char **arg)
{
	t_list	*lst;
	int	i;

	i = 0;
	while (++i < ft_strstrlen(arg))
	{
		lst = ft_getloc_struct(arg[i]);
		if (lst)
			ft_lstdel_link(&lst, ft_lstdelone, arg[i]);
		lst = ft_getenv_struct(arg[i]);
		if (lst)
			ft_lstdel_link(&lst, ft_lstdelone, arg[i]);
	}
}	