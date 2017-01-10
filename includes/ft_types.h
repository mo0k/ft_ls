/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:53:17 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/10 02:59:53 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPES_H
# define FT_TYPES_H

typedef struct			s_file
{
	struct stat			*s;
	char				*permi;
	char				*lnk;
	char				*owner;
	char				*group;
	char				*size;
	char				*date;
	char				*name;
	char				*custom_name;
	char				*path;
	int					state;
	struct s_file		*next;
	struct s_file		*prev;
	struct s_file		*node;
}						t_file;

typedef struct			s_lstall
{
	t_file				*file;
	t_file				*dir;
}						t_lstall;

typedef struct			s_opts
{
	int					singlecol;
	int					longform;
	int					stream;
	int					accesstime;
	int					statustime;
	int					timesort;
	int					reversesort;
	int					recursive;
	int					numericonly;
	int					allsort;
	int					colors;
	int					group;
	int					owner;
}						t_opts;

typedef struct dirent	t_dirent;

typedef void			(*t_pfunc)(t_file*, t_opts*);
typedef t_file			*(*t_sfunc)(t_file*, t_file*);

#endif
