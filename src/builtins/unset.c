/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 00:54:09 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/24 15:13:49 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_unset_arg_valid(char *argv, int *flag)
{
	int	j;

	if (argv == NULL)
		return (0);
	j = 0;
	while (argv[j] != '\0')
	{
		if (j == 0 && !(ft_isalpha(argv[j]) || argv[j] == '_'))
			return (print_export_error(argv, flag,
					"minishell: invalid parameter name: "));
		if (!(ft_isalnum(argv[j]) || argv[j] == '_'))
			return (print_export_error(argv, flag,
					"minishell: invalid parameter name: "));
		j++;
	}
	return (1);
}

int	does_variable_exist(char **env, char *arg)
{
	int		i;
	int		j;
	char	*tmp;
	char	*copy;

	if (*env == NULL || arg == NULL)
		return (0);
	copy = ft_strdup(arg);
	tmp = ft_strjoin(&copy, "=");
	i = 0;
	j = 0;
	while (tmp[i] != '\0')
		i++;
	while (env[j] != NULL)
	{
		if (!ft_strncmp(env[j], tmp, i))
		{
			free(tmp);
			return (j);
		}
		j++;
	}
	free(tmp);
	return (-1);
}

char	**remove_arg_from_env(char ***env, char *arg)
{
	char	**tmp;
	int		i;
	int		j;
	int		index;

	if ((*env) == NULL || arg == NULL)
		return (NULL);
	tmp = (char **)ft_calloc(ft_strlen_2d((*env)), sizeof(char *));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	j = 0;
	index = does_variable_exist(*env, arg);
	while ((*env)[i] != NULL)
	{
		if (i != index)
		{
			tmp[j] = ft_strdup((*env)[i]);
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	free_array(env);
	return (tmp);
}

int	ft_unset(char **argv, t_var **data)
{
	int		i;
	int		flag;

	if (argv == NULL)
		return (-1);
	i = 1;
	flag = 0;
	while (argv[i] != NULL)
	{
		if (is_unset_arg_valid(argv[i], &flag))
		{
			if (does_variable_exist((*data)->env, argv[i]) != -1)
				(*data)->env = remove_arg_from_env(&(*data)->env, argv[i]);
		}
		i++;
	}
	if ((*data)->env == NULL)
		return (-1);
	return (1);
}
