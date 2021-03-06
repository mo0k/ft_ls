/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/11 00:23:30 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sort.h>

void		*get_sfunc(t_opts *opts)
{
	if (!opts)
		return (NULL);
	if (opts->accesstime && opts->timesort)
		return (&merge_lst_atime);
	else if (opts->statustime && opts->timesort)
		return (&merge_lst_ctime);
	else if (opts->timesort)
		return (&merge_lst_mtime);
	else
		return (NULL);
}

t_file		*merge_lst_mtime(t_file *l1, t_file *l2)
{
	t_file	*new;

	new = NULL;
	if (!l1)
		return (l2);
	if (!l2)
		return (l1);
	if (l1->s->st_mtime < l2->s->st_mtime)
	{
		new = l2;
		new->next = merge_lst_mtime(l1, l2->next);
	}
	else
	{
		new = l1;
		new->next = merge_lst_mtime(l1->next, l2);
	}
	return (new);
}

t_file		*merge_lst_atime(t_file *l1, t_file *l2)
{
	t_file	*new;

	new = NULL;
	if (!l1)
		return (l2);
	if (!l2)
		return (l1);
	if (l1->s->st_atime < l2->s->st_atime)
	{
		new = l2;
		new->next = merge_lst_atime(l1, l2->next);
	}
	else
	{
		new = l1;
		new->next = merge_lst_atime(l1->next, l2);
	}
	return (new);
}

t_file		*merge_lst_ctime(t_file *l1, t_file *l2)
{
	t_file	*new;

	new = NULL;
	if (!l1)
		return (l2);
	if (!l2)
		return (l1);
	if (l1->s->st_ctime < l2->s->st_ctime)
	{
		new = l2;
		new->next = merge_lst_ctime(l1, l2->next);
	}
	else
	{
		new = l1;
		new->next = merge_lst_ctime(l1->next, l2);
	}
	return (new);
}
