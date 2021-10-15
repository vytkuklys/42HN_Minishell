/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 03:07:29 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/14 23:01:37 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**add_cmd(char ***history, char *cmd)
{
	char	**tmp;
	int		len;
	int		i;

	if ((*history) == NULL || cmd == NULL)
		return (NULL);
	len = ft_strlen_2d((*history));
	tmp = (char **)ft_calloc(len + 2, sizeof(char *));
	if (tmp == NULL)
		return (0);
	i = 0;
	while (i < len)
	{
		tmp[i] = ft_strdup((*history)[i]);
		i++;
	}
	tmp[i] = ft_strdup(cmd);
	tmp[i + 1] = NULL;
	free_2d_array(history);
	return (tmp);
}

int print_history(char **history)
{
	int	len;
	int	i;

	len = ft_strlen_2d(history);
	i = 0;
	while (i < len && history[i] != NULL)
	{
		printf("%d %s\n", i + 1, history[i]);
		i++;
	}
	return (0);
}

int	add_cmd_to_history(char *cmd, t_var **data)
{
	if (cmd == NULL || *data == NULL)
		return (-1);
	add_history(cmd);
	(*data)->history = add_cmd(&(*data)->history, cmd);
	if (*data == NULL)
		return (-1);
	return (0);
}