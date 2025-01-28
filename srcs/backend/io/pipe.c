/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:38:21 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 18:32:43 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

void	set_pipes(t_icmd *cmds, int nb_cmds)
{
	int	i;

	i = -1;
	while (++i < nb_cmds)
		if (pipe(cmds[i].pipe) == -1)
			return (ft_perror(1, 0/* clean_data(data) */,
					"A pipe failed to open."));
}
