/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:07:03 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/11 18:46:34 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "../../../include/minishell.h"

/* not used anywhere */

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = 0;
	while (*(s1 + len))
		len++;
	dup = gc_malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(dup + i) = *(s1 + i);
		i++;
	}
	*(dup + i) = '\0';
	return (dup);
}
