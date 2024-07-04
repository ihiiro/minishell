/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:27:42 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/04 17:06:36 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	build_list(t_token *start)
{
	t_token	*ptr;

	ptr = start;
	while (ptr->next)
		ptr = ptr->next;
	build_pipelines(ptr);
	build_redirections(ptr);
	connect_pipelines(start);
	connect_redirections(start);
}
