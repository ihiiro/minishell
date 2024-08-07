/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:16:06 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/08/05 03:06:24 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_quoted(char c)
{
	static char	quote;

	if (!quote && (c == '"' || c == '\''))
		quote = c;
	else if (c == quote)
		quote = 0;
	return (quote);
}
