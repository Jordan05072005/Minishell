/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:56:02 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/07 10:49:37 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**env2env(t_list *env)
{
	char	**new_env;
	t_list	*temp;
	size_t	len;
	size_t	i;

	temp = env;
	len = ft_lstsize(env);
	new_env = malloc((len + 1) * sizeof(char *));
	if (!new_env)
		ft_perror(1, "mini: Internal error: malloc.",
			clean_data() + clean_icmds());
	i = -1;
	while (++i < len)
	{
		new_env[i] = temp->content;
		temp = temp->next;
	}
	new_env[i] = NULL;
	return (new_env);
}
