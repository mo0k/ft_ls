/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:53:17 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/11 00:23:58 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include <ft_ls.h>

t_file	*addlst_ascii(t_file **f, t_file *prev, struct stat *s, char *path);
void	del_lst_file(t_file **f, t_opts *opts);
void	del_one(t_file **l, t_file *del, t_opts *opts);
void	ft_lstrev(t_file **f);
int		lstlen(t_file *lst);
int		lstlen_custom(t_file *lst);
void	init_file(t_file *elem);

#endif
