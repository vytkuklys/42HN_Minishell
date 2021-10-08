/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:33:01 by julian            #+#    #+#             */
/*   Updated: 2021/10/08 16:12:58 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static char	*check_dquotes(char *src)
// {
// 	int		i;
// 	int		j;
// 	char	*s;

// 	i = -1;
// 	while (src[++i] != '\0')
// 	{
// 		if (src[i] == '|' && src[i + 1] == '|' && src[i - 1] != '\\')
// 			break ;
// 	}
// 	if (i == (ft_strlen(src) - 1))
// 		return (src);
// 	else
// 	{
// 		s = (char *)malloc(sizeof(char) * i + 1);
// 		if (s == NULL)
// 			return (NULL);
// 		j = -1;
// 		while (++j < i)
// 			s[j] = src[j];
// 		s[j] = '\0';
// 		free(src);
// 		return (s);
// 	}	
// }

static int	check_second_last(char *s)
{
	int i;
	int chmod;

	chmod = 0;
	i = ft_strlen(s);
	i -= 2;
	if (s[i] == '|')
	{
		i--;
		chmod = 1;
	}
	while (s[i] == ' ' && i)
		i--;
	if (s[i] == '|')
	{
		if (chmod == 1)
		{
			printf("minishell: parse error near `||'\n");
			return (1);
		}
		printf("minishell: parse error near `|'\n");
			return (1);
	}
	return (0);
}

static int	check_parse_error(char *s)
{
	int i;

	i = 0;
	while (s[++i] != '\0')
	{
		if (s[i] == '|' && s[i + 1] == ' ' && s[i + 2] == '|' \
			&& s[i - 1] != '\\')
		{
			if (s[i + 3])
			{
				if (s[i + 3] == '|')
				{
					printf("minishell: parse error near `||'\n");
					return (1);
				}
			}
			printf("minishell: parse error near `|'\n");
			return (1);
		}
	}
	return (0);
}

static int	check_parse_error_beginning(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '|')
	{
		if (s[i + 1] == '|')
			printf("minishell: parse error near `||'\n");
		else
			printf("minishell: parse error near `|'\n");
		return (1);
	}
	else
		return (0);
}

int	check_pipes(char **cmd_line)
{	
	if (check_parse_error_beginning(*cmd_line))
		return (1);
	if (check_parse_error(*cmd_line))
		return (1);
	if (check_second_last(*cmd_line))
		return(1);
	//*cmd_line = check_dquotes(*cmd_line);
	return (0);
}


// int	check_pipes(t_operators *op, char **cmd_line)
// {	
// 	//*cmd_line = trim_pipes(*cmd_line);
// 	if (check_parse_error_beginning(*cmd_line))
// 		return (1);
// 	if (check_parse_error(*cmd_line))
// 		return (1);
// 	*cmd_line = check_dquotes(*cmd_line);
// 	op->pipes = exists_pipes(*cmd_line);
// 	return (0);
// }