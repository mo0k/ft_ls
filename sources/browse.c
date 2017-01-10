/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 03:41:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int				browse_first_node(t_file **lst, t_opts *o, t_pfunc p, t_sfunc s)
{
	t_file		*tmp;
	int			len;

	len = lstlen_custom(*lst);
	tmp = *lst;
	while (tmp)
	{
		if (tmp->s->st_mode && S_ISDIR(tmp->s->st_mode))
		{
			if (!(browse_dir(tmp->path, &tmp->node, o, s)))
				return (0);
			if (o && o->longform && tmp->node)
				set_list_to_string(tmp->node, o);
			print_root_dir(tmp, len, p, o);
			if (o && o->recursive)
				if (browse_node(&tmp->node, o, p, s))
					del_lst_file(&tmp->node, o);
		}
		del_one(lst, tmp, o);
		tmp = tmp->next;
	}
	return (1);
}

static int		browse_dir_error(char *path, t_opts *opts)
{
	char		*error;
	char		*name;

	if (!(name = ft_strrchr(path, '/')))
		name = path;
	else
		name++;
	if (opts && opts->recursive)
	{
		print_header_dir(path);
		error = ft_strjoin("ft_ls: ", name);
		perror(error);
		free(error);
		return (1);
	}
	error = ft_strjoin("ft_ls: ", name);
	perror(error);
	free(error);
	return (0);
}

int				browse_dir(char *path, t_file **lst, t_opts *opts, t_sfunc s)
{
	DIR			*dir;
	t_dirent	*x;

	dir = opendir(path);
	if (dir == NULL)
		return (browse_dir_error(path, opts)) ? (2) : (0);
	while ((x = readdir(dir)))
	{
		if (opts && opts->allsort)
		{
			if (!file_stat(path, x->d_name, lst))
				return (0);
		}
		else
		{
			if (ft_strchr(x->d_name, '.') != x->d_name)
				if (!file_stat(path, x->d_name, lst))
					return (0);
		}
	}
	sort(lst, opts, s);
	if (closedir(dir) == -1)
		return (0);
	return (1);
}
