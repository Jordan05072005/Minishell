/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:16:11 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/04 09:08:11 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*create_path(char *first_component, char *second_component)
{
	char	*path;
	char	*dir_path;

	if (first_component[ft_strlen(first_component) - 1] != '/')
		path = ft_strjoin(first_component, "/");
	else
		path = ft_strdup(first_component);
	dir_path = ft_strjoin(path, second_component)
	ft_del(path);
	return (dir_path)
}
