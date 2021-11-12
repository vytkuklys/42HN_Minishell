/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_argv_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:58:05 by vkuklys           #+#    #+#             */
/*   Updated: 2021/11/04 13:15:29 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**delete_str(char ***argv, int nth)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = (char **)ft_calloc(ft_strlen_2d((*argv)), sizeof(char *));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while ((*argv)[i] != NULL)
	{
		if (i != nth)
		{
			tmp[j] = ft_strdup((*argv)[i]);
			j++;
		}
		else
			tmp[j - 1] = ft_triple_strjoin(&tmp[j - 1], " ",
					(*argv)[i], ft_strlen(tmp[j - 1]));
		i++;
	}
	tmp[j] = NULL;
	free_array(argv);
	return (tmp);
}

char	*redirection_start(char **argv)
{
	char	*tmp;
	char	*empty;	

	empty = " \b";
	tmp = NULL;
	tmp = ft_strjoin2(&empty, *argv);
	free(*argv);
	argv = NULL;
	return (tmp);
}

int	split_argv(char ***argv, int v[2], int hash, t_var **data)
{
	int	line;
	int	chr;

	if (data == NULL)
		data = NULL;
	line = v[0];
	chr = v[1];
	if (hash == 0 && chr == 0 && ft_strlen((*argv)[line])
		== get_r_num(&(*argv)[line][chr]))
	{
		if ((!ft_strcmp((*argv)[0], "echo") && line > 1)
			|| (ft_strcmp((*argv)[0], "echo") && line > 0))
			*argv = delete_str(argv, line);
	}
	if (hash == 4)
		*argv = add_str_4(argv, line, chr);
	else if (hash == 3 && line != 0)
		*argv = add_str_3(argv, line, chr);
	else if (hash == 2)
		*argv = add_str_2(argv, line, chr);
	else if (hash == 0 && line == 1 && chr == 0)
		argv[0][1] = redirection_start(&argv[0][1]);
	if (*argv == NULL)
		return (-1);
	return (0);
}

int	iterate_til_index(char ***r, t_var **data, int nth, int hash)
{
	int	v[2];
	int	hash_nth;

	v[0] = 0;
	hash_nth = 0;
	while (r[0][v[0]] != NULL)
	{
		v[1] = 0;
		while (r[0][v[0]][v[1]] != '\0')
		{
			if (r[0][v[0]][v[1]] == '<' || r[0][v[0]][v[1]] == '>')
			{
				if (hash_nth == nth)
					return (split_argv(r, v, hash, data));
				while (r[0][v[0]][v[1] + 1] == '<' \
					|| r[0][v[0]][v[1] + 1] == '>')
					v[1]++;
				hash_nth++;
			}
			(*data)->counter++;
			v[1]++;
		}
		v[0]++;
	}
	return (0);
}

int	modify_argv(char ***argv, int *hash, t_var **data)
{
	int	i;

	i = 0;
	if (argv == NULL || data == NULL)
		argv = NULL;
	while (hash[i] != -1)
	{
		if (iterate_til_index(argv, data, i, hash[i]) == -1)
			return (-1);
		i++;
	}
	(*data)->counter = 0;
	return (0);
}
