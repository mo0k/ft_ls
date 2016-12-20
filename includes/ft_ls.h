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

#include <libft.h>

# define USAGE ft_putstr("usage: ./ft_ls [-Ralrt1] [file ...]\n");

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
	struct s_lst_file 	*next;
	struct s_lst_file 	*prev;
	struct s_lst_file 	*node;
}						t_lst_file;

typedef struct	s_lst_all
{
	t_lst_file 	*t_file;
	t_lst_file 	*t_dir;
}				t_lst_all;

typedef t_lst_file 	*(*t_sort_func)(t_lst_file**, t_lst_file*, struct stat*, const char*);
typedef void 		(*t_print_func)(t_lst_file*);

#include <padding.h>

typedef struct	s_options
{
	char 				*sort;
	char				*display;
}						t_opts;

char 					*convert_permi(char nbr);
char 					*get_permi(char *nbr, mode_t	m);
char 					get_filetype(mode_t	m);
int 					file_stat(char *path, char *filename, t_lst_file **lst, t_opts *options);
int 					browse_dir(char *path, t_lst_file **lst, t_opts *options);
int 	browse_first_node(t_lst_file **lst, t_opts *options, t_print_func);
int 					browse_node(t_lst_file **lst, t_opts *option, t_print_func);
int		get_total_blocks(t_lst_file *lst);
char					*verif_filepath(char *path);
int 	prepare_path_recursion(t_lst_file *lst);
void 	print_header_dir(char *pathdir, int state);
void 	print_first_node(t_lst_file *lst, int len, int *state, t_print_func);
int print(t_lst_file *lst, t_print_func);
void 	*get_print_func(t_opts *options);

t_lst_file		*add_lst_ascii(t_lst_file **f, t_lst_file *prev, struct stat *s, const char *name);
t_lst_file				*add_lst_time(t_lst_file **f, t_lst_file *prev, struct stat *s, const char *name);
t_lst_file		*add_lst(t_lst_file **f, t_lst_file *prev, struct stat *s, const char *name);
void	set_elem_stat(t_lst_file *elem, struct stat *s, char *name);
void	set_elem_to_string(t_lst_file *elem);
void					del_lst_file(t_lst_file **f);
void					del_one(t_lst_file **l, t_lst_file *del);
void 		print_option_l(t_lst_file *f);
void 		print_option_1(t_lst_file *f);
void 		print_normal(t_lst_file *f);
void 		print_root_file(t_lst_file *f, t_opts *opts, void (*func)(t_lst_file*));
int						lst_sort(t_lst_file **l);
void 	ft_lstrev(t_lst_file **f);
int		lstlen_custom(t_lst_file *lst);
void					swap_element(t_lst_file **elem1, t_lst_file **elem2);

t_lst_all				*check_input(int ac, char **av, t_opts *all_options, t_opts **options);
int 			check_typefile(t_lst_all *lst, char const *str, t_opts *opts);

int						is_options(char const *str);
int						is_option_valid(char const *str, char *all_options);
int			add_char(char **dst, char c);
int						stock_options(t_opts **options, char const *str);
void 		del_options(t_opts **options);
int 					stock_filepath(t_lst_file **lst, char const *str, t_opts *opts);//, t_opts *all_opts);

#endif