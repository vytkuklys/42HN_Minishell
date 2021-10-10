/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:18:05 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/04 02:31:47 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include "../libft/libft.h" 

char	*get_next_line(int fd);
// int		ft_strlen(const char *str);
// char	*ft_strdup(const char *str1);
// void	*ft_calloc(unsigned int num, unsigned int size);
// char	*ft_strjoin(char **s1, const char *s2);

#endif