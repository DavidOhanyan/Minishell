/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:32:47 by kdaniely          #+#    #+#             */
/*   Updated: 2023/07/04 13:20:45 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <libft.h>
#include <stdio.h>

static t_node	*alloc_and_check(void);

t_node	*new_pipeline_node(t_node *left, t_node *right)
{
	t_node	*node;

	node = alloc_and_check();
	node->type = PipelineNode;
	node->value.pipeline.in_fd = -42;
	node->value.pipeline.out_fd = -42;
	node->value.pipeline.left = left;
	node->value.pipeline.right = right;
	return (node);
}

t_node	*new_command_node(t_cmdtype type, t_node *prefix, t_node *command)
{
	t_node	*node;

	node = alloc_and_check();
	node->type = CommandNode;
	node->value.cmd.type = type;
	node->value.cmd.prefix = prefix;
	node->value.cmd.command = command;
	return (node);
}

t_node	*new_scommand_node(t_node *word, t_node *suffix)
{
	t_node	*node;

	node = alloc_and_check();
	node->type = SimpleCommandNode;
	node->value.s_cmd.word = word;
	node->value.s_cmd.suffix = suffix;
	return (node);
}

t_node	*new_ccommand_node(t_node *list, t_node *suffix)
{
	t_node	*node;

	node = alloc_and_check();
	node->type = CompoundCommandNode;
	node->value.c_cmd.list = list;
	node->value.c_cmd.suffix = suffix;
	return (node);
}

static t_node	*alloc_and_check(void)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	node->is_last = 0;
	return (node);
}
