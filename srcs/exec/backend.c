/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:35:06 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/29 14:25:36 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	main(int ac, char **av, char **env)
{
	t_cmd	input[2];
	char	*args1[] = {"./../../../fdf/fdf", "../../../fdf/maps/t1.fdf", NULL};
	char	*args2[] = {"grep", "fps", NULL};

	input[0].in = NULL;
	input[0].out = NULL;
	input[0].here_doc = NULL;
	input[0].args = args1;
	input[0].append = 0;
	input[1].in = NULL;
	input[1].out = NULL;
	input[1].here_doc = NULL;
	input[1].args = args2;
	input[1].append = 1;
	ft_printf("\n\n\nExit code is %d\n", exec(1, input, env));
	(void) ac;
	(void) av;
}
