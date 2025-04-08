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

void	free_tpars(t_pars **pars)
{
	(*pars)->in = NULL;
	(*pars)->out = NULL;
	ft_del((*pars)->cmd);
	(*pars)->cmd = NULL;
	(*pars)->limiter = NULL;
	(*pars)->append = NULL;
	(*pars)->sep = 0;
	(*pars)->pipe = 0;
}

t_pars	*init_struct_pars()
{
	t_pars	*cmd;

	cmd = malloc(sizeof(t_pars));
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->cmd = NULL;
	cmd->limiter = NULL;
	cmd->append = NULL;
	cmd->sep = 0;
	cmd->pipe = 0;
	cmd->exe = NULL;
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
