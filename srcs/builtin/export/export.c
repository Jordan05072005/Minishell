/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:30:03 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/07 15:30:03 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini.h"

int	ft_export(char **arg)
{
	t_data *d;
	int	i;

	i = 0;
	d = data();
	printf("hello");
	if (ft_strslen(arg) > 1)
	{
		while (arg[++i])
		{
			printf("%s", arg[i]);
			if (ft_strchr(arg[i], '=') || !ft_getloc(arg[i])) // gèrer t=t===t=t -> t="t===t=t"
				ft_lstadd_back(&(d->env), ft_lstnew((void *)arg[i]));
			else
				ft_lstadd_back(&d->env, ft_lstnew(ft_getloc(arg[i])));
		}
	}
	return (0);
}