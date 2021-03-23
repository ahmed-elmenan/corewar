/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 21:57:06 by aait-ihi          #+#    #+#             */
/*   Updated: 2021/03/23 16:44:28 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
#include "../libft/libft.h"

# define BUFF_SIZE 1000
# define L 5000
# define TMP 5001
# define BS BUFF_SIZE

int		get_next_line(const int fd, char **line);

#endif
