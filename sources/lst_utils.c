
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 03:41:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lst.h>

void			init_lstfile(t_lst_file *elem)
{
	elem->name = NULL;
	elem->custom_name = NULL;
	elem->path = NULL;
	elem->node = NULL;
	elem->owner = NULL;
	elem->group = NULL;
	elem->size = NULL;
	elem->date = NULL;
	elem->state = 0;
}

void 			ft_lstrev(t_lst_file **f)
{
	t_lst_file	*current;
	t_lst_file	*tmp;
	t_lst_file	*end;

	end = *f;
	current = *f;
	while (current)
	{
		if(!current->next)
			end = current;
		tmp = current->next;
		current->next = current->prev;
		current->prev = tmp;
		current = tmp;
	}
	*f = end;
}

int				lstlen_custom(t_lst_file *lst)
{
	int			ret;
	t_lst_file	*begin;

	ret = 0;
	begin = lst;
	while (begin)
	{
		ret++;
		begin = begin->next;
		if (ret > 1)
			return (ret);
	}
	return (ret);
}

int				lstlen(t_lst_file *lst)
{
	int			ret;
	t_lst_file	*begin;

	ret = 0;
	begin = lst;
	while (begin)
	{
		ret++;
		begin = begin->next;
	}
	return (ret);
}
