/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 20:30:37 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/20 18:39:44 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
# define CC cache->content

int	ft_distrub(char *buff, char **line, char **cache)
{
	char	*swp;

	if (ft_strchr(buff, '\n') != NULL)
	{
		swp = *line;
		*line = ft_strnjoin(*line, buff, ft_clettercount(buff, '\n'));
		ft_strdel(&swp);
		swp = *cache;
		*cache = ft_strdup(ft_strchr(buff, '\n') + 1);
		ft_strdel(&swp);
		return (1);
	}
	else if (ft_strchr(buff, '\n') == NULL)
	{
		swp = *line;
		*line = ft_strjoin(*line, buff);
		buff[0] = 0;
		ft_strdel(&swp);
	}
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*cache;
	char			buff[BUFF_SIZE + 1];
	int				ret;

	if (fd < 0 || line == NULL || read(fd, NULL, 0) < 0)
		return (-1);
	if (!head && (head = ft_lstnew("\0", fd)) == NULL)
		return (-1);
	cache = head;
	if (cache->content_size != (size_t)fd)
		cache = ft_lst_nb_chr_n_add(&head, fd);
	*line = ft_strdup("\0");
	if (CC && ft_distrub(CC, line, (char **)&(CC)) == 1)
		return (1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (ft_distrub(buff, line, (char **)&(CC)) == 1)
			return (1);
	}
	return ((ft_strlen(*line) != 0) ? 1 : 0);
}














// void			ft_free_lst(t_list **lst)
// {
// 	t_list *tmp;

// 	if (!lst)
// 		return ;
// 	while (*lst != NULL)
// 	{
// 		tmp = (*lst)->next;
// 		free(*lst);
// 		*lst = tmp;
// 	}
// 	*lst = NULL;
// }

// static t_list	*ft_check_fd(t_list **head, const int fd)
// {
// 	t_list *tmp;
// 	tmp = *head;
// 	while (tmp)
// 	{
// 		if (tmp->content_size == (size_t)fd)
// 			return (tmp);
// 		tmp = tmp->next;
// 	}
// 	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
// 		return (NULL);
// 	tmp->content_size = (size_t)fd;
// 	tmp->content = ft_strnew(0);
// 	ft_lstadd(head, tmp);
// 	return (tmp);
// }

// static int		ft_is_new_line(t_list *tmp, char *buff, char **line)
// {
// 	char *str;
// 	char *p;

// 	if ((p = ft_strchr(buff, '\n')))
// 	{
// 		*p = '\0';
// 		*line = ft_strjoin(tmp->content, buff);
// 		free(tmp->content);
// 		tmp->content = ft_strdup(p + 1);
// 		return (1);
// 	}
// 	else
// 	{
// 		str = ft_strjoin(tmp->content, buff);
// 		ft_memdel((void **)&(tmp->content));
// 		tmp->content = str;
// 	}
// 	return (0);
// }

// static void		remove_node(t_list **lst, const int fd)
// {
// 	t_list *curr;
// 	t_list *prev;

// 	prev = NULL;
// 	curr = *lst;
// 	while (curr != NULL)
// 	{
// 		if (curr->content_size == (size_t)fd)
// 		{
// 			if (prev == NULL)
// 				*lst = curr->next;
// 			else
// 				prev->next = curr->next;
// 			free(curr->content);
// 			free(curr);
// 			return ;
// 		}
// 		prev = curr;
// 		curr = curr->next;
// 	}
// }

// int				get_next_line(const int fd, char **line)
// {
// 	static t_list	*element = NULL;
// 	char			buff[BUFF_SIZE + 1];
// 	int				ret;
// 	t_list			*tmp;

// 	if (read(fd, buff, 0) < 0 || !line)
// 		return (-1);
// 	ret = 1;
// 	if (!(tmp = ft_check_fd(&element, fd)))
// 		return (0);
// 	ft_strcpy(buff, (char *)tmp->content);
// 	ft_bzero(tmp->content, ft_strlen(tmp->content));
// 	while (ret > 0)
// 	{
// 		if (ft_is_new_line(tmp, buff, line))
// 			return (1);
// 		ret = read(fd, buff, BUFF_SIZE);
// 		buff[ret > 0 ? ret : 0] = '\0';
// 	}
// 	if ((ret = ft_strlen(tmp->content))
// 			&& (*line = ft_strdup(tmp->content)))
// 		((char *)tmp->content)[0] = '\0';
// 	remove_node(&element, fd);
// 	return (ret != 0);
// }