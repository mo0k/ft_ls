/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:53:17 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/10 02:59:54 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <stdio.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <uuid/uuid.h>
# include <sys/ioctl.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <libft.h>
# include <ft_types.h>
# include <input.h>
# include <lst.h>
# include <sort.h>
# include <padding.h>
# include <print.h>

# define OPTIONS "1GRacglnortu"

void	usage(void);
int		file_stat(char *path, char *filename, t_file **lst);
int		browse_first_node(t_file **lst, t_opts *opts, t_pfunc p, t_sfunc s);
int		browse_node(t_file **lst, t_opts *opts, t_pfunc pfunc, t_sfunc sfunc);
int		browse_dir(char *path, t_file **lst, t_opts *opts, t_sfunc sfunc);

#endif
