/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:32:33 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/08/02 19:54:58 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	clear_list(t_gc *gl)
{
	t_gc	*tmp;

	while (gl)
	{
		tmp = gl->next;
		free(gl->garbage);
		free(gl);
		gl = tmp;
	}
}

static void	*add_to_garbage_list(t_gc **gl, void *mem)
{
	t_gc	*ptr;

	if (!mem)
		return (clear_list(*gl), NULL);
	if (!*gl)
	{
		*gl = malloc(sizeof(t_gc));
		if (!*gl)
			return (NULL);
		(*gl)->garbage = mem;
		(*gl)->next = NULL;
	}
	else
	{
		ptr = *gl;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = malloc(sizeof(t_gc));
		if (!ptr->next)
			return (clear_list(*gl), NULL);
		ptr->next->garbage = mem;
		ptr->next->next = NULL;
	}
	return (mem);
}

void	*gc_malloc(size_t size, int lever)
{
	static t_gc	*garbage_list;
	void		*mem;

	mem = NULL;
	if (!lever)
		clear_list(garbage_list);
	else
	{
		mem = malloc(size);
		if (!mem)
			return (clear_list(garbage_list), NULL);
		if (!add_to_garbage_list(&garbage_list, mem))
			return (clear_list(garbage_list), NULL);
	}
	return (mem);
}
