/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:41:54 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/28 18:58:20 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../backend.h"

char	*get_path(t_cmd cmd)
{
	char	**tries;
	char	*paths;
	char	*path;
	char	*temp;
	int		i;

	// if (!cmd.args)
	// 	return (ft_perror(1, 0/* clean_data(data) */, "Error happened during split."),
	// 		NULL);
	// if (!data->cmd_arg[0])
	// 	return (ft_perror(-1, 0, "Empty argument as function."), NULL);
	i = -1;
	paths = getenv("PATH");
	tries = ft_split(paths, ':');
	while (tries && tries[++i])
	{
		temp = ft_strjoin(tries[i], "/");
		path = ft_strjoin(temp, cmd.args[0]);
		ft_del(temp);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_tab((void **)tries, count_words(paths, ':')), path);
		ft_del(path);
	}
	ft_free_tab((void **)tries, count_words(paths, ':'));
	return (NULL);
}
