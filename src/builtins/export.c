/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:48:21 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/08 03:58:11 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **add_arg_to_env(char ***env, char *arg)
{
	char	**tmp;
	int		len;
	int		i;

	if ((*env) == NULL || arg == NULL)
		return NULL;
	len = ft_strlen_2d((*env));
	tmp = (char **)ft_calloc(len + 2, sizeof(char *));
	if (tmp == NULL)
		return 0;
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
	free_2d_array(env);
	return (tmp);	
}

int is_arg_valid(char *argv, int *flag)
{
	int	j;

	if (argv == NULL)
		return (0);
	j = 0;
	while (argv[j] != '\0' && argv[j] != '=')
	{
		if (j == 0 && !(ft_isalpha(argv[j]) || argv[j] == '_'))
			return (print_export_error(argv, flag
				,"minishell: not an identifier: "));
		if (!(ft_isalnum(argv[j]) || argv[j] == '_'))
			return (print_export_error(argv, flag
				, "minishell: not an identifier: "));
		j++;
	}
	if (argv[j] != '=')
		return (0);
	return (1);
}

int does_variable_exist(char **env, char *arg)
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
	index = does_variable_exist(env, arg);
	if (index == -1)
		return (-1);
	tmp = env[index];
	env[index] = ft_strdup(arg);
	free(tmp);
	tmp = NULL;
	return (0);
}

char	*ft_export(char *cmd_line, t_var **data)
{
	char	**argv;
	int		i;
	int		flag;

	argv = get_variables(cmd_line);
	if (argv == NULL)
		return (NULL);
	i = 1;
	flag = 0;
	while (argv[i] != NULL)
	{
		if (is_arg_valid(argv[i], &flag))
		{
			if (does_variable_exist((*data)->env, argv[i]) != -1)
			{
				modify_arg_in_env((*data)->env, argv[i]);
			}
			else
				(*data)->env = add_arg_to_env(&(*data)->env, argv[i]);
		}
		i++;
	}
	free_2d_array(&argv);
	return (NULL);
}

// int main(int argc, char **argv)
// {
// 	char *cmd_line;
//     t_var   *data;

// 	char *env[5];

// 	env[0] = "ABC=123";
// 	env[1] = "A=123";
// 	env[2] = "B=123";
// 	env[3] = "TEMP=1";
// 	env[4] = NULL;
//     data = (t_var *)malloc(sizeof(t_var));
// 	if (!data)
// 		return (-1);
// 	if (argc == 0 && argv == NULL)
// 		argc = 0;
//     init_env(env, &data);
// 	ft_export("export TEMP=123", &data);

// 	int i = 0;
// 	while(data->env[i] != NULL)
// 	{
// 		printf("%s", data->env[i]);
// 		i++;
// 	}
// 	return 0;
// }