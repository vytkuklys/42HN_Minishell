/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:46:15 by jludt             #+#    #+#             */
/*   Updated: 2021/11/05 10:32:15 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_in(char ***argv, int pos)
{
	int		i;
	int		in;

	i = -1;
	while (argv[pos][++i] != NULL)
	{
		if (!ft_strcmp(argv[pos][i], "<"))
		{
			i++;
			in = open(argv[pos][i], O_RDONLY);
			if (in < 0)
			{
				pr_error(strerror(errno), argv[pos][i]);
				return (-1);
			}
			if (dup2(in, STDIN_FILENO) < 0)
			{
				perror("DUP2 FAILED");
				return (-1);
			}
		}
	}
	close(in);
	update_argv(argv, "<", pos);
	return (1);
}

int	redirect_append(char ***argv, int pos)
{
	int		i;
	int		out;

	i = -1;
	while (argv[pos][++i] != NULL)
	{
		if (!ft_strcmp(argv[pos][i], ">>"))
		{
			i++;
			out = open(argv[pos][i], O_CREAT | O_RDWR | O_APPEND, 0644);
			if (out < 0)
			{
				pr_error(strerror(errno), argv[pos][i]);
				return (-1);
			}
			if (dup2(out, STDOUT_FILENO) < 0)
			{
				perror("DUP2 FAILED");
				return (-1);
			}
		}	
	}
	close(out);
	update_argv(argv, ">>", pos);
	return (1);
}

int	redirect_out(char ***argv, int pos)
{
	int		i;
	int		out;

	i = -1;
	while (argv[pos][++i] != NULL)
	{
		if (!ft_strcmp(argv[pos][i], ">"))
		{
			i++;
			out = open(argv[pos][i], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (out < 0)
			{
				pr_error(strerror(errno), argv[pos][i]);
				return (-1);
			}
			if (dup2(out, STDOUT_FILENO) < 0)
			{
				perror("DUP2 FAILED");
				return (-1);
			}
		}
	}
	close(out);
	update_argv(argv, ">", pos);
	return (1);
}

int	handle_redirections(char ***argv, int pos)
{
	int	i;

	i = -1;
	while (argv[pos][++i] != NULL)
	{		
		if (!ft_strcmp(argv[pos][i], ">"))
		{
			if (redirect_out(argv, pos) == -1)
				return (-1);
			i = -1;
		}
		else if (!ft_strcmp(argv[pos][i], ">>"))
		{
			if (redirect_append(argv, pos) == -1)
				return (-1);
			i = -1;
		}
		else if (!ft_strcmp(argv[pos][i], "<"))
		{
			if (redirect_in(argv, pos) == -1)
				return (-1);
			i = -1;
		}
	}
	return (0);
}
