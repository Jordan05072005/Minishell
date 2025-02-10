/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:40:22 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/10 15:44:11 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_color(int option)
{
	static char	col[3][22] = {"\001\033[38;2;000;161;201m\002",
		"\001\033[38;2;000;255;161m\002",
		"\001\033[38;2;000;208;181m\002"};

	return (col[option]);
}

// void	set_bit(char *col, char *bit, int offset)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	len = ft_strlen(bit);
// 	i = -1;
// 	while (++i < len - 3)
// 		col[i + offset] = '0';
// 	j = -1;
// 	while (bit[++j])
// 	{
// 		col[i + offset] = bit[j];
// 		i++;
// 	}
// }

// int	set_color(char *col, int color)
// {
// 	char	*bit;

// 	bit = ft_itoa((color >> 16) & 0xFF);
// 	if (!bit)
// 		return (1);
// 	set_bit(col, bit, 8);
// 	ft_del(bit);
// 	bit = ft_itoa((color >> 8) & 0xFF);
// 	if (!bit)
// 		return (1);
// 	set_bit(col, bit, 12);
// 	ft_del(bit);
// 	bit = ft_itoabit;
// 	if (!bit)
// 		return (1);
// 	set_bit(col, bit, 16);
// 	ft_del(bit);
// 	return (0);
// }

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

int	set_colors(char	*col1, char *col2, char *col3)
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
	return (0);
}
