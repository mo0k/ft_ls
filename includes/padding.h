/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/10 02:59:49 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PADDING_H
# define PADDING_H

# include <ft_ls.h>

size_t	is_strlen_max(char *str);
int		*array_strlen_max(t_file *lst_file);
void	set_padding_long(t_file **lst_file);
void	set_padding_normal(t_file **lst_file, int len_max);
size_t	lnk_strlen_max(t_file *lst_file);
size_t	owner_strlen_max(t_file *lst_file);
size_t	group_strlen_max(t_file *lst_file);
size_t	size_strlen_max(t_file *lst_file);
size_t	name_strlen_max(t_file *lst_file);

#endif
