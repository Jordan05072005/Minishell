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

#include "mini.h"

void ft_lstdel_link(t_list **l, void *content)
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
	ft_lstdelone(temp, free);
}

int	ft_unset(char **arg)
{
	t_list	*lst;
	t_list	*prev;
	size_t	i;

	i = 0;
	while (arg[++i])
	{
		lst = ft_getloc_struct(arg[i], &prev);
		if (lst)
			return (ft_lstdelink(&prev, &lst, ft_del), 0);
		lst = ft_getenv_struct(arg[i], &prev);
		if (lst)
			ft_lstdelink(&prev, &lst, ft_del);
	}
	return (0);
}	