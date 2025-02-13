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

// void	putenv(t_list *d)
// {
// 	char	*temp;
// 	t_list	*cpy;
// 	int			i;

// 	cpy = d;
// 	i = 0;
// 	while (ft_lstsize(cpy) != i)
// 	{
// 		temp = cpy->content;
// 		while (cpy)
// 		{
// 			if (ft_strncmp(temp, cpy->content, ft_strlen(temp) + 1) > 0)
// 		}
// 	}
// 	temp = 
// }

int	ft_export(char **arg)
{
	t_data *d;
	int	i;

	i = 0;
	d = data();
	if (ft_strslen(arg) > 1)
	{
		while (arg[++i])
		{
			printf("%s", arg[i]);
			if (ft_strchr(arg[i], '=') || !ft_getloc(arg[i])) // gèrer t=t===t=t -> t="t===t=t"
				ft_lstadd_back(&(d->env), ft_lstnew(ft_strdup(arg[i])));
			else
				ft_lstadd_back(&d->env, ft_lstnew(ft_strdup(ft_getloc(arg[i]))));
		}
	}
	// else
	// 	putenv(d);
	return (0);
}