/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:41:49 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/27 21:17:19 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(dest);
	if (n <= len)
		return (ft_strlen(src) + n);
	while (src[i] && i < n - len - 1)
	{
		dest[i + len] = src[i];
		i++;
	}
	dest[i + len] = 0;
	return (len + ft_strlen(src));
}
