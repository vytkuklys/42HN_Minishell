/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:48:21 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/19 18:59:39 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**add_arg_to_env_status(char ***env, char *arg)
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

static int	does_export_var_exists_status(char **env, char *arg)
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

static int	modify_arg_in_env_status(char **env, char *arg)
{
	int		index;
	char	*tmp;

	if ((*env) == NULL || arg == NULL)
		return (-1);
	index = does_export_var_exists_status(env, arg);
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

int	ft_status(t_var **data)
{
	char	*argv;

	argv = ft_strjoin_status("?=", ft_itoa((*data)->status));
	if (does_export_var_exists_status((*data)->env, argv) != -1)
	{
		if (modify_arg_in_env_status((*data)->env, argv) == -1)
			return (-1);
	}
	else
		(*data)->env = add_arg_to_env_status(&(*data)->env, argv);
	return (1);
}
