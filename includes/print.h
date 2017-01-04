/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/05 14:53:12 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

#include <ft_ls.h>
#include <colors.h>

void 	print_root_file(t_lst_file *f, t_options *opts, t_print_func print_func);
void 	print_root_dir(t_lst_file *lst, int len, t_print_func printfunc, t_options *opts);
void 	print_header_dir(char *pathdir);
void	print_totalblocks(t_lst_file *lst);
int 	print(t_lst_file *lst, t_print_func, t_options *opts);
void 	*get_print_func(t_options *options);
void 	print_longform(t_lst_file *f, t_options *opts);
void 	print_singlecol(t_lst_file *f, t_options *opts);
void 	print_stream(t_lst_file *f, t_options *opts);
void 	set_list_to_string(t_lst_file *lst, t_options *opts);
void	set_elem_to_string(t_lst_file *elem, t_options *opts);
void 	rights_xattr(char *path, char *rights);
char 	*get_time(t_lst_file *elem, t_options *opts);

#endif