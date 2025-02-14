/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 02:50:33 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/28 02:50:33 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	in_str(char c, char *sep, int y)
{
	int	i;

	i = -1;
	if (y != -1)
	{
		if (sep[y] == c)
			return (1);
		return (0);
	}
	while (sep[++i])
	{
		if (sep[i] == c)
			return (1);
	}
	return (0);
}

int	nbr_sep(char **str, char *sep)
{
	int	i;
	int	compt;

	i = 0;
	compt = 0;
	while (str[i])
	{
		if (strncmp(str[i], sep, ft_strlen(sep)) == 0)
			compt++;
		i++;
	}
	return (compt + 1);
}

int	is_var(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (i != 0 && i != (ft_strlen(str) - 1) && str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	free_tpars(t_pars **pars)
{
	(*pars)->in = NULL;
	(*pars)->out = NULL;
	ft_del((*pars)->cmd);
	(*pars)->cmd = NULL;
	(*pars)->limiter = NULL;
	(*pars)->append = NULL;
	(*pars)->sep = 0;
}

void	shift_left(char **str, size_t i)
{
	// write(1, "here", 4);
	if (i > ft_strslen(str) || !str)
		return ;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}	
