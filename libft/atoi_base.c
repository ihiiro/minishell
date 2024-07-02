/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 04:02:09 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/14 04:02:10 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_value(char a)
{
	if (ft_isdigit(a))
		return (a - '0');
	else if (a >= 'a' && a <= 'f')
		return (a - 'a' + 10);
	else if (a >= 'A' && a <= 'F')
		return (a - 'A' + 10);
	return (-1);
}

void	skip_spaces(char *str, int *sign, int *i, int base)
{
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
		(*i)++;
	*sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (base == 16)
	{
		if (str[*i] == '0'
			&& (str[*i + 1] == 'x' || str[*i + 1] == 'X'))
			(*i) += 2;
	}
}

int	atoi_base(char *str, int base)
{
	int	sign;
	int	res;
	int	t;
	int	i;

	if (base <= 0 || base > 16)
		return (-1);
	i = 0;
	skip_spaces(str, &sign, &i, base);
	res = 0;
	while (1)
	{
		t = get_value(str[i]);
		if (t == -1)
			break ;
		res = res * base + t;
		i++;
	}
	return (sign * res);
}
