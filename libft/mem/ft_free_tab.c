/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:56:44 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/12 14:16:35 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_tab(void **tab, size_t size)
{
	void	**temp;
	size_t	i;

	i = -1;
	temp = tab;
	while (++i < size)
		ft_del2((void **)&(*tab++));
	ft_del2((void **)&temp);
}
