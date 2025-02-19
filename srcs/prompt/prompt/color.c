/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:40:22 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/19 13:09:37 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//Plan to mess with the piscine, see with NIDRUON
char	*get_color(int option)
{
	static char	col[4][22] = {"\001\033[38;2;000;161;201m\002",
		"\001\033[38;2;000;255;161m\002",
		"\001\033[38;2;000;208;181m\002",
		"\001\033[38;2;255;255;255m\002"};

	return (col[option]);
}

void	set_color(char *col, int color)
{
	int	bit;

	bit = (color >> 16) & 0xFF;
	col[8] = '0' + bit / 100;
	col[9] = '0' + (bit / 10) % 10;
	col[10] = '0' + bit % 10;
	bit = (color >> 8) & 0xFF;
	col[12] = '0' + bit / 100;
	col[13] = '0' + (bit / 10) % 10;
	col[14] = '0' + bit % 10;
	bit = color & 0xFF;
	col[16] = '0' + bit / 100;
	col[17] = '0' + (bit / 10) % 10;
	col[18] = '0' + bit % 10;
}

int	set_colors(char	*col1, char *col2, char *col3, char *col4)
{
	int		color;

	color = ft_atoi_base(col1 + 2, "0123456789abcdef", 16);
	if (color == -1)
		return (1);
	set_color(get_color(0), color);
	color = ft_atoi_base(col2 + 2, "0123456789abcdef", 16);
	if (color == -1)
		return (2);
	set_color(get_color(1), color);
	color = ft_atoi_base(col3 + 2, "0123456789abcdef", 16);
	if (color == -1)
		return (3);
	set_color(get_color(2), color);
	color = ft_atoi_base(col4 + 2, "0123456789abcdef", 16);
	if (color == -1)
		return (3);
	set_color(get_color(3), color);
	return (0);
}
