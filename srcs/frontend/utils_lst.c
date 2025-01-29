/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:59:50 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/28 17:59:50 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *init_struct(char **split, int nbr)
{
	t_cmd	*cmd;
	int	i;

	cmd = malloc(sizeof(t_cmd) * (nbr));
	i = -1;
	while (++i < nbr)
	{
		cmd[i].split = split;
		cmd[i].in = NULL;
		cmd[i].out = NULL;
		cmd[i].cmd = ft_strdup("");
		cmd[i].limiter = NULL;
		cmd[i].append = NULL;
		cmd[i].sep = 0;
	}
	return (cmd);
}