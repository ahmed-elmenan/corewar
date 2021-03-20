/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:25:43 by anel-bou          #+#    #+#             */
/*   Updated: 2021/03/20 18:39:53 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
#include "../libft/libft.h"

# define BUFF_SIZE 32

int		get_next_line(const int fd, char **line);

#endif
