/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:01:40 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/18 00:02:52 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_variables(char *cmd_line, t_var **data)
{
	char	**argv;
	int		argc;

	argc = get_argc(cmd_line);
	if (argc == -1)
	{
		write(1, "minishell: invalid command line arguments \n", 44);
		return (NULL);
	}
	argv = (char **)malloc((argc + 1) * sizeof(char *));
	if (argv == NULL)
		return (NULL);
	get_argv(cmd_line, argv, (*data)->env);
	return (argv);
}

int	init_env(char **env, t_var **data)
{
	int	i;
	int	len;

	len = ft_strlen_2d(env);
	(*data)->env = ft_calloc(len + 1, sizeof(char *));
	if ((*data)->env == NULL)
		return (-1);
	i = 0;
	while (env[i] != NULL)
	{
		(*data)->env[i] = ft_strdup(env[i]);
		i++;
	}
	(*data)->env[i] = NULL;
	return (0);
}

int	init_data(char **env, t_var **data)
{
	if (init_env(env, data) == -1)
		return (-1);
	(*data)->error = 0;
	(*data)->exit = 0;
	(*data)->history = (char **)malloc((1) * sizeof(char *));
	(*data)->history[0] = NULL;
	return (0);
}
