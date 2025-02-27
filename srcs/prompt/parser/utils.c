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

int	ft_strchri(char *str, char *c)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (c[++j])
		{
			if (str[i] == c[j])
				return (i);
		}
	}
	return (i);
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


char	*ft_strdelchar(char *str, char del)
{
	int	i;
	int	len;
	char	*str_f;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != del)
			len++;
	}
	str_f = malloc(sizeof(char) * (len + 1));
	if (!str_f)
		return (NULL);
	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != del)
			str_f[len++] = str[i];
	}
	str_f[len] = 0;
	return (ft_del(str), str_f);
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
