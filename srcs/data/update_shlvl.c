/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:40:27 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/19 13:57:36 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	update_shlvl(void)
{
	t_list	*shlvl;
	t_list	*bin;
	char	*temp;
	int		value;

	shlvl = ft_getenv_struct("SHLVL", &bin);
	if (!shlvl)
		return (ft_lstadd_back(&(data()->env), ft_lstnew(ft_strdup("SHLVL=1\
"))));
	value = ft_atoi(shlvl->content + 6) + 1;
	ft_del(shlvl->content);
	if (value < 0)
		value = 0;
	temp = ft_itoa(value);
	if (value > 999)
	{
		ft_perror(-1, ft_strsjoin((const char *[]){"mini: warning: shell le\
vel (", temp, ") too high, resetting to 1.", NULL}), 0);
		shlvl->content = ft_strdup("SHLVL=1");
		ft_del(temp);
		return ;
	}
	shlvl->content = ft_strsjoin((const char *[]){"SHLVL=", temp, NULL});
	ft_del(temp);
}
