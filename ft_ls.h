/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/05 14:53:12 by jmoucade         ###   ########.fr       */
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
}				t_lst_file;

#include <padding.h>
#include <libft.h>

char					*verif_filepath(char *path);

char 					*convert_permi(char nbr);
char 					*get_permi(char *nbr, mode_t	m);
char 					get_filetype(mode_t	m);

int 					file_stat(char *path, char *filename, t_lst_file **lst);
t_lst_file				*add_lst(t_lst_file **f);
void 					print_lst(t_lst_file *f);

#endif