/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/10 02:59:48 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include <ft_ls.h>
# include <colors.h>

void	print_root_file(t_file *f, t_opts *opts, t_pfunc pfunc);
void	print_root_dir(t_file *lst, int len, t_pfunc pfunc, t_opts *opts);
void	print_header_dir(char *pathdir);
void	print_totalblocks(t_file *lst);
int		print(t_file *lst, t_pfunc pfunc, t_opts *opts);
void	*get_pfunc(t_opts *options);
void	print_longform(t_file *f, t_opts *opts);
void	print_singlecol(t_file *f, t_opts *opts);
void	print_stream(t_file *f, t_opts *opts);
void	set_list_to_string(t_file *lst, t_opts *opts);
void	set_elem_to_string(t_file *elem, t_opts *opts);
void	rights_xattr(char *path, char *rights);
char	*get_time(t_file *elem, t_opts *opts);

#endif
