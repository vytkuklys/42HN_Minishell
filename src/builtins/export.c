/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:48:21 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/24 13:21:15 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**add_arg_to_env(char ***env, char *arg)
{
	char	**tmp;
	int		len;
	int		i;

	if ((*env) == NULL || arg == NULL)
		return (NULL);
	len = ft_strlen_2d((*env));
	tmp = (char **)ft_calloc(len + 2, sizeof(char *));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (i == len - 1)
			tmp[i] = ft_strdup(arg);
		else
			tmp[i] = ft_strdup((*env)[i]);
		i++;
	}
	tmp[i] = ft_strdup((*env)[i - 1]);
	tmp[i + 1] = NULL;
	free_array(env);
	return (tmp);
}

int	is_arg_valid(char *argv, int *flag)
{
	int	j;

	if (argv == NULL)
		return (0);
	j = 0;
	while (argv[j] != '\0' && argv[j] != '=')
	{
		if (j == 0 && !(ft_isalpha(argv[j]) || argv[j] == '_'))
			return (print_export_error(argv, flag,
					"minishell: not an identifier: "));
		if (!(ft_isalnum(argv[j]) || argv[j] == '_'))
			return (print_export_error(argv, flag,
					"minishell: not an identifier: "));
		j++;
	}
	if (argv[j] != '=')
		return (0);
	return (1);
}

int	does_export_var_exists(char **env, char *arg)
{
	int	i;
	int	j;

	if (*env == NULL || arg == NULL)
		return (0);
	i = 0;
	j = 0;
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	if (arg[i] == '=' && arg[i + 1] != '\0')
	{
		while (env[j] != NULL)
		{
			if (!ft_strncmp(env[j], arg, i + 1))
				return (j);
			j++;
		}
	}
	return (-1);
}

int	modify_arg_in_env(char **env, char *arg)
{
	int		index;
	char	*tmp;

	if ((*env) == NULL || arg == NULL)
		return (-1);
	index = does_export_var_exists(env, arg);
	if (index == -1)
		return (0);
	tmp = env[index];
	env[index] = ft_strdup(arg);
	if (env[index] == NULL)
		return (-1);
	free(tmp);
	tmp = NULL;
	return (0);
}

int	ft_export(char **argv, t_var **data)
{
	int		i;
	int		flag;

	i = 0;
	while (argv[i] != NULL)
		i++;
	if (i == 1 && !ft_strcmp(argv[0], "export"))
		return (print_export((*data)->env));
	i = 1;
	flag = 0;
	while (argv[i] != NULL)
	{
		if (is_arg_valid(argv[i], &flag))
		{
			if (does_export_var_exists((*data)->env, argv[i]) != -1)
			{
				if (modify_arg_in_env((*data)->env, argv[i]) == -1)
					return (-1);
			}
			else
				(*data)->env = add_arg_to_env(&(*data)->env, argv[i]);
		}
		i++;
	}
	return (1);
}
