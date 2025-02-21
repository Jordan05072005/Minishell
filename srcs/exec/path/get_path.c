/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:41:54 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/21 14:13:27 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_cmd_path(t_cmd input)
{
	char	**tries;
	char	*paths;
	char	*path;
	int		i;

	i = -1;
	paths = ft_getenv("PATH");
	if (!paths)
		return (ft_perror(-1, ft_strsjoin((const char *[]){"mini: \
", input.args[0], " No such file or directory.", NULL}), 0), NULL);
	tries = ft_split(paths, ':');
	if (!tries)
		return (ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds()), NULL);
	while (tries[++i])
	{
		path = create_path(tries[i], input.args[0]);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_tab((void **)tries, count_words(paths, ':')), path);
		ft_del(path);
	}
	return (ft_free_tab((void **)tries, count_words(paths, ':')), NULL);
}

char	*get_path(t_cmd input, t_icmd *cmd)
{
	if (!input.args)
		return (NULL);
	if (!input.args[0])
		return (NULL);
	if (is_builtin(input.args[0]) || (access(input.args[0], F_OK) == 0
			&& ft_strnstr(input.args[0], "/", ft_strlen(input.args[0]))))
		return (ft_strdup(input.args[0]));
	if (ft_strchr(input.args[0], '='))
	{
		cmd->define = 1;
		return (NULL);
	}
	return (get_cmd_path(input));
}
