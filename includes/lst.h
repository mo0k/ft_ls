/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:53:17 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 00:40:35 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

#include <ft_ls.h>

t_lst_file		*add_lst_ascii(t_lst_file **f, t_lst_file *prev, struct stat *s, char *name);
void			del_lst_file(t_lst_file **f, t_options *opts);
void			del_one(t_lst_file **l, t_lst_file *del, t_options *opts);
void 			ft_lstrev(t_lst_file **f);
int				lstlen(t_lst_file *lst);
int				lstlen_custom(t_lst_file *lst);
void 			init_lstfile(t_lst_file *elem);

#endif