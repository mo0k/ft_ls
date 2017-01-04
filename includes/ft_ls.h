/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:53:17 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 00:40:35 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <uuid/uuid.h>
#include <sys/ioctl.h>

#include <sys/xattr.h>
#include <sys/acl.h>

#include <libft.h>

# define USAGE ft_putstr("usage: ./ft_ls [-Raclrtu1] [file ...]\n");

#define OPTIONS "1RacgGlnortu"

typedef struct	s_lst_file
{
	struct stat 		*s;
	char 				*permi;
	char				*lnk;
	char				*owner;
	char				*group;
	char				*size;
	char				*date;
	char				*name;
	char				*custom_name;
	char				*path;
	int 				state;
	struct s_lst_file 	*next;
	struct s_lst_file 	*prev;
	struct s_lst_file 	*node;
}						t_lst_file;

typedef struct	s_lst_all
{
	t_lst_file 	*t_file;
	t_lst_file 	*t_dir;
}				t_lst_all;

typedef struct	s_opts
{
	int			singlecol;
	int			longform;
	int			stream;
	int			accesstime;
	int			statustime;
	int			timesort;
	int			reversesort;
	int			recursive;
	int 		numericonly;
	int 		allsort;
	int 		colors;
	int 		group;
	int 		owner;
}				t_options;

typedef void 			(*t_print_func)(t_lst_file*, t_options*);
typedef t_lst_file 		*(*t_sort_func)(t_lst_file*, t_lst_file*);

#include <input.h>
#include <lst.h>
#include <sort.h>
#include <padding.h>
#include <print.h>

int 					file_stat(char *path, char *filename, t_lst_file **lst);
int 					browse_first_node(t_lst_file **lst, t_options *options, t_print_func, t_sort_func sortfunc);
int 					browse_node(t_lst_file **lst, t_options *options, t_print_func printfunc, t_sort_func sortfunc);
int 					browse_dir(char *path, t_lst_file **lst, t_options *options, t_sort_func sortfunc);

#endif