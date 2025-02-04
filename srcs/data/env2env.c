/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:56:02 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/04 16:58:17 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**env2env(t_list *env)
{
	char	**new_env;
	t_list	*temp;
	size_t	len;
	size_t	i;

	temp = env;
	len = ft_lstsize(env);
	new_env = ft_calloc(len + 1, sizeof(char *));//not protected
	i = -1;
	while (++i < len)
	{
		new_env[i] = temp->content;
		temp = temp->next;
	}
	return (new_env);
}
