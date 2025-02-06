/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:35:04 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/05 21:40:02 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		len;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1) - 1;
	start = 0;
	while (start <= len && ft_strchr(set, s1[start]))
		start ++;
	while (len >= 0 && ft_strchr(set, s1[len]))
		len --;
	if (start <= len)
		return (ft_substr(s1, start, len - start + 1));
	return (ft_calloc(1, sizeof(char)));
}
