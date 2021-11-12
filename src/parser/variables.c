/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:26:37 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/25 08:55:47 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_var_len(const char *s, char *cmd_line)
{
	int		l;
	int		nth;
	char	*tmp;

	l = 0;
	if (s == NULL || cmd_line == NULL)
		return (-1);
	nth = get_dollar_num(cmd_line) - get_dollar_num(s);
	tmp = cmd_line;
	if (!ft_strcmp((char *)s, "$?"))
		return (1);
	while (nth-- >= 0)
		tmp = ft_strchr(tmp, '$');
	while (tmp[l + 1] != '\0' && (ft_isalnum(tmp[l + 1]) || tmp[l + 1] == '_'))
		l++;
	return (l);
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

int	remove_var(char **arg, int index, char *cmd_line)
{
	int	var_len;

	if (*arg == NULL)
		return (-1);
	var_len = get_var_len(*arg, cmd_line) + 1;
	*arg = ft_triple_strjoin(arg, "", &(*arg)[index + var_len], index);
	return (-1);
}

int	expand_variable(char **arg, char **env, char quote, char *cmd_line)
{
	char	*variable;
	char	*tmp;
	int		index;
	int		i;

	if (cmd_line == NULL)
		return (-1);
	tmp = *arg;
	i = -1;
	while (tmp[++i] != '\0' && quote != '\'')
	{
		if (tmp[i] == '$' && tmp[i + 1] != ' ' && tmp[i + 1] != '\0')
		{
			variable = ft_substr(&tmp[i], 1, get_var_len(tmp, cmd_line));
			index = does_variable_exist(env, variable);
			if (index != -1)
				i += replace_var_with_value(env[index], &tmp, i);
			else
				i += remove_var(&tmp, i, cmd_line);
			free(variable);
		}
	}
	if (quote != '\'')
		*arg = tmp;
	return (-1);
}
