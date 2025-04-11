/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:23:08 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/07 10:52:46 by hle-hena         ###   ########.fr       */
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
