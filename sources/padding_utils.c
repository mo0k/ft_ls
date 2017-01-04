/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/10 18:49:13 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <padding.h>

size_t			lnk_strlen_max(t_lst_file *lst_file)
{
	size_t		len_max;

	len_max = 0;
	while (lst_file)
	{
		len_max = is_strlen_max(lst_file->lnk);
		lst_file = lst_file->next;
	}
	is_strlen_max(NULL);
	return (len_max);
}

size_t			owner_strlen_max(t_lst_file *lst_file)
{
	size_t		len_max;
	
	len_max = 0;
	while (lst_file)
	{
		len_max = is_strlen_max(lst_file->owner);
		lst_file = lst_file->next;
	}
	is_strlen_max(NULL);
	return (len_max);
}

size_t			group_strlen_max(t_lst_file *lst_file)
{
	size_t		len_max;

	len_max = 0;
	while (lst_file)
	{
		len_max = is_strlen_max(lst_file->group);
		lst_file = lst_file->next;
	}
	is_strlen_max(NULL);
	return (len_max);
}

size_t			size_strlen_max(t_lst_file *lst_file)
{
	size_t		len_max;

	len_max = 0;
	while (lst_file)
	{
		len_max = is_strlen_max(lst_file->size);
		lst_file = lst_file->next;
	}
	is_strlen_max(NULL);
	return (len_max);
}

size_t			name_strlen_max(t_lst_file *lst_file)
{
	size_t		len_max;

	len_max = 0;
	while (lst_file)
	{
		len_max = is_strlen_max(lst_file->name);
		lst_file = lst_file->next;
	}
	is_strlen_max(NULL);
	return (len_max);
}
