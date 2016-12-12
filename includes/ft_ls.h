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
	char 				*permi;
	char				*lnk;
	char				*owner;
	char				*group;
	char				*size;
	char				*date;
	char				*name;
	struct s_lst_file 	*next;
	struct s_lst_file 	*prev;
}						t_lst_file;

typedef struct			s_lst_input
{
	char				*name;
	t_lst_file			*tfile;
	struct s_lst_input	*next;
}						t_lst_input;

#include <padding.h>

char 					*convert_permi(char nbr);
char 					*get_permi(char *nbr, mode_t	m);
char 					get_filetype(mode_t	m);
int 					file_stat(char *filename, t_lst_file **lst);
int 					browse_dir(char *path, t_lst_file **lst);
char					*verif_filepath(char *path);

t_lst_file				*add_lst_file(t_lst_file **f, t_lst_file *prev);
t_lst_input				*add_lst_input(t_lst_input **f);
void					del_lst_file(t_lst_file **f);
void					del_lst_input(t_lst_input **l);
void					del_one(t_lst_file **l, t_lst_file *del);
void 					print_lst_file(t_lst_file *f);
void 					print_lst_input(t_lst_input *f);
int						lst_sort(t_lst_file **l);
void					swap_element(t_lst_file **elem1, t_lst_file **elem2);

t_lst_input				*check_input(int ac, char **av, char *all_options, char **options);
int						is_options(char const *str);
int						is_option_valid(char const *str, char *all_options);
int						stock_options(char **options, char const *str);
int 					stock_filepath(t_lst_input **lst, char const *str);

#endif