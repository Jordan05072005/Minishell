/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define2child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:41:47 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/28 16:39:38 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**copy_args(char **src)
{
	char	**dest;
	int		len;

	len = ft_strslen(src);
	dest = ft_calloc(len + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	dest[len--] = NULL;
	while (len >= 0)
	{
		dest[len] = src[len];
		len--;
	}
	return (dest);
}

void	define2child(t_icmd *cmds, int nb_cmds, int child, int start)
{
	char	**temp;
	t_cmd	path_finder;

	temp = copy_args(&(cmds[child].args[start]));
	if (!temp)
		ft_perror(1, ft_strdup("mini: Internal error: malloc."),
				clean_data() + clean_icmds());
	cmds[child].args = temp;
	path_finder = (t_cmd){NULL, NULL, temp, NULL, 0, 0, NULL};
	cmds[child].type = ft_tern_int(is_builtin(cmds[child].args[0]), 2, 1);
	cmds[child].path = get_path(path_finder, &cmds[child]);
	cmds[child].type = -1;
	if (cmds[child].type == 1 && nb_cmds == 1)
	{
		cmds[child].pid = fork();
		if (cmds[child].pid == -1)
			ft_perror(1, ft_strdup("mini: Internal error: process."),
				clean_data() + clean_icmds());
		if (cmds[child].pid != 0)
			return ;
	}
	if (!is_builtin(cmds[child].args[0]))
		exec_child(cmds, nb_cmds, child);
	exec_builtin(cmds, nb_cmds, child);
}
