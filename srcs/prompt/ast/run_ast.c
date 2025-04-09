/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:36:34 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/09 14:36:43 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	run_list(char *line)
{
	int		rv;
	t_data	*da;
	t_pars	*p;

	da = data();
	p = parseur(line);
	da->pars = p;
	rv = exec(p->pipe, p->exe);
	clean_pars(p);
	da->pars = NULL;
	return (rv);
}

int	run_ast(t_bt *ast)
{
	int	rv;

	if (!ast)
		return (-1);
	if (!ast->left && !ast->right)
		return (run_list((char *)ast->content));
	rv = run_ast(ast->left);
	if (ft_strncmp("&&", (char *)ast->content, 3) == 0)
	{
		if (rv == 0)
			return (run_ast(ast->right));
		else
			return (rv);
	}
	else
	{
		if (rv != 0)
			return (run_ast(ast->right));
		else
			return (rv);
	}
}
