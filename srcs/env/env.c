/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:56:52 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/29 17:16:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#inlcude "env.h"

char **env(void)
{
	static char	**env = NULL;

	return (env);
}
