/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:35:06 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/27 17:52:55 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "backend.h"

int	exec(int nb_cmds, t_cmd *cmds, char **env)
{
	if (nb_cmds == 0)
		return (0);
	
}