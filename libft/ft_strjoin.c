/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:08:20 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/17 10:18:56 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		len1;
	int		len2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1 && s2)
		return ((char *)s2);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = gc_malloc(sizeof(char) * len1 + len2 + 1, COLLECT);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, len1 + 1);
	ft_strlcat(ptr, s2, len1 + len2 + 1);
	return (ptr);
}
