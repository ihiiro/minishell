/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:38:13 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/02 11:38:14 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*simple_pwd(char *pwd, char *home)
{
	char	*rest_path;
	char	*simplified;
	int		len;

	if (!home)
		return (pwd);
	len = ft_strlen(home);
	if (ft_strncmp(pwd, home, ft_strlen(home)))
		return (pwd);
	rest_path = ft_substr(pwd, len, ft_strlen(pwd) - len);
	simplified = ft_strjoin("~", rest_path);
	return (simplified);
}

char	*ps1_prompt(char *pwd, char *home)
{
	char	*prompt;
	char	*tmp;

	tmp = ORANGE"┏━"RED"🅼.🆂.🅷 "ORANGE"════«\e[30m"RED;
	prompt = ft_strjoin(tmp, simple_pwd(pwd, home));
	prompt = ft_strjoin(prompt, "\e[0m"ORANGE"»\n┗━☿️\e[0m ");
	if (!prompt)
		return (NULL);
	return (prompt);
}

int	check_line(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (1);
		str++;
	}
	return (0);
}
