/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_argv_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 13:35:15 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/31 20:49:34 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_redirection_type(char *cmd_line, int index)
{
	int	i;

	i = 0;
	if (index > 0 && cmd_line[index - 1] == ' ')
	{
		while (cmd_line[index + i] == '>' || cmd_line[index + i] == '<')
			i++;
		if (cmd_line[index + i] == ' ')
			return (1);
		return (2);
	}
	while (cmd_line[index + i] == '>' || cmd_line[index + i] == '<')
		i++;
	if (cmd_line[index + i] == ' ')
		return (3);
	return (4);
}

int	get_r_num(char *cmd_line)
{
	int	i;

	i = 0;
	if (cmd_line == NULL)
		return (0);
	while ((cmd_line[i] == '<' || cmd_line[i] == '>') && cmd_line[i] != '\0')
		i++;
	return (i);
}

char	**add_str_4(char ***argv, int line, int chr)
{
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	i = -1;
	tmp = (char **)ft_calloc(ft_strlen_2d((*argv)) + 3, sizeof(char *));
	if (tmp == NULL)
		return (NULL);
	while ((*argv)[++i] != NULL)
	{
		if (i != line)
			tmp[j] = ft_strdup((*argv)[i]);
		else
		{
			tmp[j++] = ft_substr((*argv)[i], 0, chr);
			tmp[j++] = ft_substr((*argv)[i], chr, get_r_num(&(*argv)[i][chr]));
			tmp[j] = ft_substr((*argv)[i], chr + get_r_num(&(*argv)[i][chr]),
					ft_strlen((*argv)[i]) - chr + get_r_num(&(*argv)[i][chr]));
		}
		j++;
	}
	free_array(argv);
	tmp[j] = NULL;
	return (tmp);
}

char	**add_str_3(char ***argv, int line, int chr)
{
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = (char **)ft_calloc(ft_strlen_2d((*argv)) + 2, sizeof(char *));
	if (tmp == NULL)
		return (NULL);
	while ((*argv)[i] != NULL)
	{
		if (i != line)
			tmp[j] = ft_strdup((*argv)[i]);
		else
		{
			tmp[j++] = ft_substr((*argv)[i], 0, chr);
			tmp[j] = ft_substr((*argv)[i], chr, get_r_num(&(*argv)[i][chr]));
		}
		j++;
		i++;
	}
	free_array(argv);
	tmp[j] = NULL;
	return (tmp);
}

char	**add_str_2(char ***argv, int line, int chr)
{
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = (char **)ft_calloc(ft_strlen_2d((*argv)) + 2, sizeof(char *));
	if (tmp == NULL)
		return (NULL);
	while ((*argv)[i] != NULL)
	{
		if (i != line)
			tmp[j] = ft_strdup((*argv)[i]);
		else
		{
			tmp[j++] = ft_substr((*argv)[i], 0, get_r_num(&(*argv)[i][chr]));
			tmp[j] = ft_substr((*argv)[i], chr + get_r_num(&(*argv)[i][chr]),
					ft_strlen((*argv)[i]) - chr + get_r_num(&(*argv)[i][chr]));
		}
		j++;
		i++;
	}
	free_array(argv);
	tmp[j] = NULL;
	return (tmp);
}
