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

#include "mini.h"

t_pars	*init_struct_pars(char **split, int sep)
{
	t_pars	*cmd;
	int		i;

	if (sep <= 0)
		return (NULL);
	cmd = malloc(sizeof(t_pars) * (sep));
	i = -1;
	while (++i < sep)
	{
		cmd[i].split = split;
		cmd[i].in = NULL;
		cmd[i].out = NULL;
		cmd[i].cmd = NULL;
		cmd[i].limiter = NULL;
		cmd[i].append = NULL;
		cmd[i].sep = 0;
	}
	return (cmd);
}

void	init_struct_cmd(t_pars **pars, int nbr, char **arg)
{
	int	i;

	(*pars)->exe = malloc(sizeof(t_cmd) * nbr);
	i = -1;
	(*pars)->pipe = nbr;
	while (++i < nbr)
	{
		(*pars)->exe[i].in = NULL;
		(*pars)->exe[i].out = NULL;
		(*pars)->exe[i].args = NULL;
		(*pars)->exe[i].here_doc = NULL;
		(*pars)->exe[i].append = 0;
		(*pars)->exe[i].split = arg;
	}
}
