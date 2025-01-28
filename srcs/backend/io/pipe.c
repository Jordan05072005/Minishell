/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:38:21 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 10:49:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

void	set_pipes(t_icmd *cmds, int nb_cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		if (pipe(cmds[i].pipe) == -1)
			return (ft_perror(1, 0/* clean_data(data) */,
					"A pipe failed to open."));
}
