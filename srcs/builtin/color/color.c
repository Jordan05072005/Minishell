/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:16:06 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/11 16:15:42 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**get_config(int config)
{
	static char *configs[7][4] = {
		{NULL, "0x00a1c9", "0x00ffa1", "0x00d0b5"},
		{NULL, "0x501941", "0x63264a", "0x5c1653"},
		{NULL, "0xcc8eeb", "0xcc8eeb", "0xb649ed"},
		{NULL, "0xc0d684", "0xcbeaa6", "0xf3f9d2"},
		{NULL, "0x593f62", "0x7b6d8d", "0x6a5678"},
		{NULL, "0x775144", "0xc09891", "0x9c756b"},
		{NULL, "0x7e8d85", "0xa2e3c4", "0xabd1be"}
	};

	return (configs[config]);
}

int ft_color(char **av)
{
	static int	config = 0;
	char		**colors;
	int			i;

	i = 0;
	colors = av;
	if (!av[1])
	{
		config = (config + 1) % 7;
		colors = get_config(config);
	}
	else
	{
		while (++i < 4 && av[i])
		{
			ft_tolower(av[i]);
			if (ft_strncmp(av[i], "0x", 2))
				return (ft_perror(-1, ft_strsjoin((const char *[]){"color: Inva\
lid hex ('", av[i], "').", NULL}), 0), 1);
		}
	}
	if (i != 4 - (i == 0) * 4)
		return (ft_perror(-1, ft_strdup("color: Wrong number of arguments."),
				0), 1);
	return (set_colors(colors[1], colors[2], colors[3]));
}
