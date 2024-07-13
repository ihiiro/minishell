/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   para.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:07:52 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/13 09:10:15 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../include/minishell.h"

static t_token	*find_para_open(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == PARA_OPEN)
			return (tokens);
		tokens = tokens->prev;
	}
	return (NULL);
}

static void	simplify(t_token *para_open, t_token **head)
{
	t_token	*para;
	t_token	*skip;

	skip = para_open;
	while (skip && skip->type != PARA_CLOSE)
		skip = skip->next;
	skip = skip->next;
	para = gc_malloc(sizeof(t_token), COLLECT);
	para->type = PARA;
	para->next = skip;
	if (skip)
		skip->prev = para;
	para->prev = para_open->prev;
	para->word = NULL;
	para->name = NOT_OP;
	para->subtree = fetch_ast(para_open);
	para->subtree->token->subshell = 1;
	if (para_open->prev)
		para_open->prev->next = para;
	else
		*head = para;
}

void	connect_para(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->subtree && tokens->subtree->left
			&& tokens->subtree->left->token
			&& tokens->subtree->left->token->type == PARA)
			tokens->subtree->left = tokens->prev->subtree;
		if (tokens->subtree && tokens->subtree->right
			&& tokens->subtree->right->token
			&& tokens->subtree->right->token->type == PARA)
			tokens->subtree->right = tokens->next->subtree;
		tokens = tokens->next;
	}
}

static void	point_at_para_subtrees(t_token *para_open)
{
	while (para_open && para_open->type != PARA_CLOSE)
	{
		if (para_open->subtree && para_open->subtree->left
			&& para_open->subtree->left->token
			&& para_open->subtree->left->token->type == PARA)
			para_open->subtree->left = para_open->prev->subtree;
		if (para_open->subtree && para_open->subtree->right
			&& para_open->subtree->right->token
			&& para_open->subtree->right->token->type == PARA)
			para_open->subtree->right = para_open->next->subtree;
		para_open = para_open->next;
	}
}

t_token	*simplify_para(t_token *tokens)
{
	t_token	*para_open;
	t_token	*head;

	head = tokens;
	while (tokens)
	{
		if (tokens->type == PARA_CLOSE)
		{
			para_open = find_para_open(tokens);
			build_pipelines(tokens);
			build_redirections(tokens);
			connect_pipelines(para_open);
			connect_redirections(para_open);
			simplify(para_open, &head);
			point_at_para_subtrees(para_open);
		}
		tokens = tokens->next;
	}
	return (head);
}
