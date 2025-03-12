/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:23:08 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/12 14:09:54 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_del(void *add)
{
	if (add)
	{
		free(add);
		add = NULL;
	}
}

void	ft_del2(void **add)
{
	if (add && *add)
		{
			free(*add);
			*add = NULL;
		}
}
