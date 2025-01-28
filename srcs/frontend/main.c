/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:33:09 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/27 16:33:09 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//penser a clear l'history
int	main()
{
	char	*line;
	char	*before;
	char	*prompt;

	before = NULL;
	signal(SIGINT, new_prompt);
	prompt = get_prompt();
	line = readline(prompt);
	while (line)
	{
		if (!before || ft_strncmp(before, line, ft_strlen(before)) != 0)
			add_history(line);
		if (before)
			free(before);
		before = line;
		if (parseur(line) == 0)
			return 1;
		line = readline(prompt);
	}
	free(prompt);
	return (1);
}


int main2() {
    printf("Texte à effacer...");
    fflush(stdout); // Assurez-vous que le texte est bien affiché avant de manipuler le curseur

    // Séquence d'échappement pour effacer la ligne actuelle
    printf("\033[K");
		printf("\033[G"); // replacer le curseur au debut de la ligne;

    // Reste du texte ou nouvelle entrée
    printf("Nouvelle ligne après effacement\n");

    return 0;
}