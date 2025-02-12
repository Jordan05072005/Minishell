/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:17:00 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/12 18:20:08 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_env(void *str, void *to_find)
{
	char	*line;
	int		size;

	size = ft_strlen(to_find);
	line = ft_strnstr(str, to_find, size);
	if (line && line[size] == '=')
		return (1);
	return (0);
}