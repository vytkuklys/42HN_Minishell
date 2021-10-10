/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:26:37 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/10 00:34:57 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int
	get_var_len(const char *s)
{
	int	len;

	if (s == NULL)
		return (-1);
	len = 0;
	while (s[len] != '\0' && s[len] != '$' && s[len] != ' ')
		len++;
	return (len);
}

int	get_len_til_symbol(char *s, char symbol)
{
	int	len;

	if (s == NULL)
		return (-1);
	len = 0;
	while (s[len] != '\0')
	{
		if (s[len] == symbol)
			return (len);
		len++;
	}
	return (-1);
}

int	replace_var_with_value(char *env, char **arg, int index)
{
	int		var_len;
	char	*value;

	if (!env || *arg == NULL)
		return (-1);
	var_len = get_len_til_symbol(env + 1, '=') + 2;
	value = ft_strchr(env, '=') + 1;
	*arg = ft_triple_strjoin(arg, value, &(*arg)[index + var_len], index);
	return (ft_strlen(value) - 1);
}

int	remove_var(char **arg, int index)
{
	int	var_len;

	if (*arg == NULL)
		return (-1);
	var_len = get_var_len(&(*arg)[index + 1]) + 1;
	*arg = ft_triple_strjoin(arg, "", &(*arg)[index + var_len], index);
	return (-1);
}

int	expand_variable(char **arg, char **env, char quote)
{
	char	*variable;
	char	*tmp;
	int		index;
	int		i;

	tmp = *arg;
	i = 0;
	while (tmp[i] != '\0' && quote != '\'')
	{
		if (tmp[i] == '$')
		{
			variable = ft_substr(&tmp[i], 1, get_var_len(&tmp[i + 1]));
			index = does_variable_exist(env, variable);
			if (index != -1)
			{
				i += replace_var_with_value(env[index], &tmp, i);
			}
			else
				i += remove_var(&tmp, i);
		}
		i++;
	}
	if (quote != '\'')
		*arg = tmp;
	return (-1);
}
