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

t_pars *init_struct_pars(char **split, int sep)
{
	t_pars	*cmd;
	int	i;

	if (sep <= 0)
		return (NULL);
	cmd = malloc(sizeof(t_pars) * (sep));
	i = -1;
	while (++i < sep)
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

t_var	*ft_same_var(t_var *lst, char *name)
{
	while (lst && lst->next)
	{
		if (!ft_strncmp(lst->name, name, ft_strlen(name)) && !ft_strncmp(lst->name, name, ft_strlen(lst->name)))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_var	*ft_varlast(t_var *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	push_back_var(t_var **v, char *name, char *data, char **split)
{
	t_var *temp;

	if (!(*v))
	{
	*v = malloc(sizeof(t_var));
	(*v)->name = name;
	(*v)->data = data;
	(*v)->split = split;
	(*v)->next = NULL;
	return ;
	}
	temp = ft_same_var(*v, name);
	if (temp)
	{
		temp->data = data;
		return ;
	}
	temp = ft_varlast(*v);
	temp->next = malloc(sizeof(t_var));
	temp->next->name = name;
	temp->next->data = data;
	temp->next->split = split;
	temp->next->next = NULL;
}
