/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:32:33 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/11 18:54:56 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	*add_to_garbage_list(t_gc **gl, void *mem)
{
	t_gc	*ptr;

	if (!mem)
		return (NULL);
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
			return (NULL);
		ptr->next->garbage = mem;
		ptr->next->next = NULL;
	}
	return (mem);
}

void	*gc_malloc(size_t size)
{
	static t_gc	*garbage_list;
	void		*mem;

	mem = malloc(size);
	if (!mem)
		return (NULL);
	if (!add_to_garbage_list(&garbage_list, mem))
		return (NULL);
	return (mem);
}
