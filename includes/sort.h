/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/11 00:24:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include <ft_ls.h>

void		sort(t_file **lst, t_opts *options, t_sfunc sfunc);
void		*get_sfunc(t_opts *options);
t_file		*merge_lst_mtime(t_file *l1, t_file *l2);
t_file		*merge_lst_atime(t_file *l1, t_file *l2);
t_file		*merge_lst_ctime(t_file *l1, t_file *l2);

#endif
