/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strequal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:28:18 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/20 16:21:29 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	strequal(char *str0, char *str1)
{
	int	rslt;

	if (!str0 || !str1)
		return (false);
	rslt = ft_strcmp(str0, str1);
	if (rslt)
		return (false);
	else
		return (true);
}
