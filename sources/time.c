/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 03:41:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

static char		*format_time(time_t time)
{
	char		*new_time;

	new_time = ft_strnew(12);
	new_time = ft_strncpy(new_time, ctime(&time) + 4, 7);
	new_time = ft_strncat(new_time, ctime(&time) + 19, 5);
	return(new_time);
}

char			*get_time(t_lst_file *elem, t_options *opts)
{
	if (opts && opts->accesstime)// && opts->timesort)
	{
		if (time(NULL) - elem->s->st_atime > 15778800 || elem->s->st_atime - time(NULL) > 3600)
			return(format_time(elem->s->st_atime));
		return(ft_strsub(ctime(&elem->s->st_atime), 4, 12));
	}
	else if (opts && opts->statustime)// && opts->timesort)
	{
		if (time(NULL) - elem->s->st_ctime > 15778800 || elem->s->st_ctime - time(NULL) > 3600)
			return(format_time(elem->s->st_ctime));
		return(ft_strsub(ctime(&elem->s->st_ctime), 4, 12));
	}
	else
	{
		if (time(NULL) - elem->s->st_mtime > 15778800 || elem->s->st_mtime - time(NULL) > 3600)
			return(format_time(elem->s->st_mtime));
		return(ft_strsub(ctime(&elem->s->st_mtime), 4, 12));
	}
}