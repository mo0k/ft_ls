/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 03:41:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

#include <ft_ls.h>

void 		sort(t_lst_file **lst, t_options *options, t_sort_func sortfunc);
void 		*get_sort_func(t_options *options);
t_lst_file	*merge_lst_mtime(t_lst_file *l1, t_lst_file *l2);
t_lst_file	*merge_lst_atime(t_lst_file *l1, t_lst_file *l2);
t_lst_file	*merge_lst_ctime(t_lst_file *l1, t_lst_file *l2);

#endif