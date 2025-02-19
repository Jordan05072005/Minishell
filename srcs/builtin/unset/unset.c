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

//Should not be able to del SHLVL apparently ...
int	ft_unset(char **arg)
{
	// t_list	*lst;
	// t_list	*prev;
	size_t	i;

	i = 0;
	while (arg[++i])
	{
		ft_lstremove_if(&(data()->loc), is_env, ft_del, arg[i]);
		ft_lstremove_if(&(data()->env), is_env, ft_del, arg[i]);
		if (!ft_strncmp(arg[i], "SHLVL", 6))
			ft_lstadd_back(&data()->env, ft_lstnew(ft_strdup("SHLVL=0")));
	}
	return (0);
}
