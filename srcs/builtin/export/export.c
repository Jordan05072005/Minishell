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

int	find_chr(char *str, int ch)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ch)
			return (i);
	}
	return (-1);
}

t_list	*ft_lstcpy(t_list *d)
{
	t_list	*cpy;

	cpy = ft_lstnew(ft_strdup(d->content));
	d = d->next;
	while (d && cpy)
	{
		ft_lstadd_back(&cpy, ft_lstnew(ft_strdup(d->content)));
		d = d->next;
	}
	return (cpy);
}

void	putexport(t_list *cpy, int size)
{
	t_list	*temp;
	t_list	*first;
	char		*temp2;
	int			i;

	first = cpy;
	i = -1;
	while (++i < size)
	{
		temp = cpy;
		while (cpy)
		{
			if (!(temp->content) || (cpy->content && ft_strncmp(temp->content, cpy->content, ft_strlen(temp->content) + 1) > 0))
				temp = cpy;
			cpy = cpy->next;
		}
		temp2 = ft_substr(temp->content, 0, find_chr(temp->content, '='));
		ft_printf("declare -x %s=\"%s\"\n", temp2, ft_getenv(temp2));
		ft_del(temp2);
		ft_del(temp->content);
		temp->content = NULL;
		cpy = first;
	}
	ft_lstclear(&cpy, ft_del);
}

int	ft_export(char **arg)
{
	t_data	*d;
	int			i;
	int			rv;

	i = 0;
	d = data();
	rv = 0;
	if (ft_strslen(arg) > 1)
	{
		while (arg[++i])
		{
			if (!rv && export_var(arg[i]))
				rv = 1;
		}
	}
	else
		putexport(ft_lstcpy(d->env), ft_lstsize(d->env));
	return (rv);
}
