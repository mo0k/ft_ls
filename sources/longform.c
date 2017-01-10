/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longform.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 21:13:13 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/11 00:23:47 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

static char		get_filetype(mode_t m)
{
	if (S_ISLNK(m))
		return ('l');
	else if (S_ISREG(m))
		return ('-');
	else if (S_ISDIR(m))
		return ('d');
	else if (S_ISCHR(m))
		return ('c');
	else if (S_ISBLK(m))
		return ('b');
	else if (S_ISFIFO(m))
		return ('p');
	else if (S_ISSOCK(m))
		return ('s');
	else
		return (0);
}

static char		*get_permi(mode_t m)
{
	char		*ret;

	ret = ft_strnew(11);
	ret[0] = get_filetype(m);
	ret[1] = (m & S_IRUSR) ? 'r' : '-';
	ret[2] = (m & S_IWUSR) ? 'w' : '-';
	ret[3] = (m & S_IXUSR) ? 'x' : '-';
	ret[3] = (m & S_IXUSR && m & S_ISUID) ? 's' : ret[3];
	ret[3] = (!(m & S_IXUSR) && m & S_ISUID) ? 'S' : ret[3];
	ret[4] = (m & S_IRGRP) ? 'r' : '-';
	ret[5] = (m & S_IWGRP) ? 'w' : '-';
	ret[6] = (m & S_IXGRP) ? 'x' : '-';
	ret[6] = (m & S_IXGRP && m & S_ISGID) ? 's' : ret[6];
	ret[6] = (!(m & S_IXGRP) && m & S_ISGID) ? 'S' : ret[6];
	ret[7] = (m & S_IROTH) ? 'r' : '-';
	ret[8] = (m & S_IWOTH) ? 'w' : '-';
	ret[9] = (m & S_IXOTH) ? 'x' : '-';
	ret[9] = (m & S_IXOTH && m & S_ISVTX) ? 't' : ret[9];
	ret[9] = (!(m & S_IXOTH) && m & S_ISVTX) ? 'T' : ret[9];
	ret[10] = ' ';
	return (ret);
}

void			rights_xattr(char *path, char *rights)
{
	int			buflen;
	acl_t		acl;

	buflen = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (buflen == -1)
		return ;
	if (buflen > 0)
		rights[10] = '@';
	else
	{
		if ((acl = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
			rights[10] = '+';
		else
			rights[10] = ' ';
		free(acl);
	}
}

void			set_elem_to_string(t_file *elem, t_opts *opts)
{
	if (!elem)
		return ;
	elem->permi = get_permi(elem->s->st_mode);
	elem->lnk = ft_itoa((int)elem->s->st_nlink);
	if (!getpwuid(elem->s->st_uid) || opts->numericonly)
		elem->owner = ft_itoa((int)elem->s->st_uid);
	else
		elem->owner = ft_strdup(getpwuid(elem->s->st_uid)->pw_name);
	if (!getgrgid(elem->s->st_gid) || opts->numericonly)
		elem->group = ft_itoa((int)elem->s->st_gid);
	else
		elem->group = ft_strdup(getgrgid(elem->s->st_gid)->gr_name);
	elem->size = ft_itoa((int)elem->s->st_size);
	elem->date = get_time(elem, opts);
}

void			set_list_to_string(t_file *lst, t_opts *opts)
{
	t_file	*node;

	node = lst;
	while (node)
	{
		set_elem_to_string(node, opts);
		node = node->next;
	}
}
