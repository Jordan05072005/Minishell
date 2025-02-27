/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 02:02:36 by jguaglio          #+#    #+#             */
/*   Updated: 2025/02/27 02:02:36 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// char	**insert_strs(char **str1, char **str2, int j)
// {
// 	int		i;
// 	int		i1;
// 	int		i2;
// 	int		len;
// 	char	**str_f;

// 	len = ft_strslen(str1) + ft_strslen(str2);
// 	str_f = malloc(sizeof(char *) * len);
// 	i = -1;
// 	i1 = -1;
// 	i2 = -1;
// 	while (++i < len)
// 	{
// 		if (i < j || i2 == (int)ft_strslen(str2))
// 			str_f[i] = str1[++i1];
// 		else
// 			str_f[i] = str2[++i2];
// 	}
// 	return (str_f);
// }

// int	name_correct(char *name, char *before, char *after, int len)
// {
// 	int	s;
// 	int	end;

// 	end = strlen(name);
// 	while (s < ft_strlen(before) && end < ft_strlen(after))
// 	{
// 		if (name[s] != before[s] || name[len - s] != after[ft_strlen(after) - end - 1])
// 			return (1);
// 		if (s < ft_strlen(before))
// 		s++;
// 		if (end < ft_strlen(after))
// 		end++;
// 	}
// 	return (0);
// 	)
// }

// char	**get_file(DIR *dir, char *before, char *after)
// {
// 	struct dirent *entry;
// 	int	start;
// 	int	end;

// 	entry = readdir(dir);
// 	while (entry != NULL) // Lire chaque fichier ou répertoire
// 	{
// 		if (name_correct(dir->dd_name, before, after, ft_strlen(dir->dd_name)));


// 		entry = readdir(dir);
// 	}
// 	printf("Nom du fichier : %s\n", entry->d_name);
// }

// si avant y'a / -> prend se chemin
// sinon reduire la recherche a avant apres 
// juste * == all
// riens on ecrit jsute *dededde = *dededde
void	wildcard(char **str, int j)
{
	DIR *dir;
	struct dirent *entry;
	// int	i = -1;

	dir = opendir(ft_getimp("PWD"));
	if (!dir)
		return ;
	(void)entry;
	(void)str;
	(void)j;
}