/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:13:43 by hle-hena          #+#    #+#             */
/*   Updated: 2025/04/09 14:38:49 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_next_sep(t_list *blocks, char *sep)
{
	blocks = blocks->next->next;
	if (!blocks)
		return (1);
	if (ft_strncmp(blocks->content, sep, 3) == 0)
		return (1);
	return (0);
}

t_bt	*build_subtree(t_list *blocks, int *move)
{
	t_bt	*subtree;
	char	*sep;

	*move = 0;
	subtree = create_bt_node(blocks->content);
	(*move)++;
	blocks = blocks->next;
	if (!blocks)
		return (subtree);
	sep = blocks->content;
	while (blocks)
	{
		set_parent(create_bt_node(blocks->content), subtree, 1);
		(*move)++;
		subtree = subtree->parent;
		if (!is_next_sep(blocks, sep))
			break ;
		blocks = blocks->next;
		set_parent(subtree, create_bt_node(blocks->content), 0);
		(*move)++;
		blocks = blocks->next;
	}
	return (subtree);
}

t_bt	*build_tree(t_list *blocks)
{
	t_bt	*tree;
	t_bt	*subtree;
	int		move;

	tree = build_subtree(blocks, &move);
	while (move--)
		blocks = blocks->next;
	while (blocks)
	{
		subtree = build_subtree(blocks, &move);
		while (move--)
			blocks = blocks->next;
		set_parent(tree, subtree, 0);
		tree = subtree;
	}
	while (tree->parent)
		tree = tree->parent;
	return (tree);
}

int	ast_ok(t_list *blocks, char *err)
{
	if (!blocks || err)
	{
		if (!err)
			err = ft_strdup("newline");
		printf("mini: syntax error near unexpected token `%s'\n", err);
		set_exit_val(2);
		return (clear_blocks(blocks), ft_del2((void **)&err), 0);
	}
	return (1);
}

t_bt	*get_ast(char *line)
{
	t_bt	*tree;
	t_list	*blocks;
	char	*err;
	size_t	i;

	err = NULL;
	if (!line)
		return (NULL);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (NULL);
	blocks = getLineParsing(line, &err);
	if (!ast_ok(blocks, err))
		return (NULL);
	blocks = ft_lstrev(blocks);
	if (ft_lstsize(blocks) == 1)
		tree = create_bt_node(blocks->content);
	else
		tree = build_tree(blocks);
	del_unusedlst(blocks);
	return (tree);
}
