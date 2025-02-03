/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:38:18 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/03 16:17:20 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	**get_stack(char *curpath, int *depth)
{
	char	**stack;
	char	**path;
	int		i;

	path = ft_split(curpath, '/');
	stack = ft_calloc(ft_strslen((const char **)path) + 1, sizeof(char *));
	ft_del(curpath);
	if (!path || !stack)
		return (ft_free_tab((void **)path, ft_strslen((const char **)path)),
			ft_del(stack), ft_perror(1, 0, "Malloc error."), NULL);
	*depth = 0;
	i = -1;
	while (path[++i])
	{
		if (!ft_strncmp(path[i], "..", 3) && *depth > 0)
			(*depth)--;
		else if (ft_strncmp(path[i], ".", 2) != 0)
		{
			if (stack[*depth])
				ft_del(stack[*depth]);
			stack[(*depth)++] = ft_strdup(path[i]);
		}
	}
	ft_free_tab((void **)path, ft_strslen((const char **)path));
	return (stack);
}

// i3[0] = depth;
// i3[1] = len / j;
// i3[2] = i;
char	*clean_curpath(char *curpath)
{
	char	*clean;
	char	**stack;
	int		i3[3];

	if (!curpath)
		return (curpath);
	stack = get_stack(curpath, &i3[0]);
	i3[1] = ft_tern_int(i3[0] == 0, 2, 1);
	i3[2] = -1;
	while (++i3[2] < i3[0])
		i3[1] += ft_strlen(stack[i3[2]]) + 1;
	clean = ft_calloc(i3[1], sizeof(char));
	if (!clean)
		return (ft_free_tab((void **)stack, ft_strslen((const char **)stack)),
			ft_perror(1, 0, "Malloc error."), NULL);
	i3[2] = -1;
	clean[0] = '/';
	i3[1] = 1;
	while (++i3[2] < i3[0])
	{
		ft_strlcpy(clean + i3[1], stack[i3[2]], ft_strlen(stack[i3[2]]) + 1);
		i3[1] += ft_strlen(stack[i3[2]]);
		if (stack[i3[2] + 1])
			clean[i3[1]++] = '/';
	}
	return (ft_free_tab((void **)stack,
			ft_strslen((const char **)stack)), clean);
}

// #include <stdio.h>
// int main()
// {
//     char *paths[] = {
//         "////home/./libft/..",
//         "/usr//local///bin/",
//         "/home/user/.././Desktop/",
//         "./././Documents///file.txt",
//         "/../..",
//         NULL
//     };

//     for (int i = 0; paths[i]; i++)
//     {
//         char *cleaned = clean_curpath(ft_strdup(paths[i]));
//         printf("Original: %s -> Cleaned: %s\n", paths[i], cleaned);
//         free(cleaned);
//     }
//     return 0;
// }

// // Original: ////home/./libft/.. -> Cleaned: /home/./libft
// // Original: /usr//local///bin/ -> Cleaned: /usr/local/bin
// // Original: /home/user/.././Desktop/ -> Cleaned: /home/./Desktop
// // Original: ./././Documents///file.txt -> Cleaned: /./././Documents/file.txt
// // Original: /../.. -> Cleaned: /�	?