/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/10 02:59:20 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sort.h>

static void		fixe_prev(t_file *lst, t_file *prev)
{
	t_file	*cur;

	cur = lst;
	if (!cur)
		return ;
	cur->prev = prev;
	fixe_prev(cur->next, cur);
}

static void		divise_lst(t_file *source, t_file **dest_1, t_file **dest_2)
{
	t_file	*t_1;
	t_file	*t_2;

	if (!source && !source->next)
	{
		*dest_1 = source;
		*dest_2 = NULL;
	}
	else
	{
		t_1 = source;
		t_2 = source->next;
		while (t_2)
		{
			t_2 = t_2->next;
			if (t_2)
			{
				t_1 = t_1->next;
				t_2 = t_2->next;
			}
		}
		*dest_1 = source;
		*dest_2 = t_1->next;
		t_1->next = NULL;
	}
}

static void		merge_sort(t_file **lst, t_sfunc sfunc)
{
	t_file	*current;
	t_file	*lst_1;
	t_file	*lst_2;

	current = *lst;
	if (!current || !current->next || !sfunc)
		return ;
	divise_lst(current, &lst_1, &lst_2);
	merge_sort(&lst_1, sfunc);
	merge_sort(&lst_2, sfunc);
	*lst = sfunc(lst_1, lst_2);
	fixe_prev(*lst, NULL);
}

void			sort(t_file **lst, t_opts *opts, t_sfunc sfunc)
{
	if (!lst || !*lst)
		return ;
	if (sfunc)
		merge_sort(lst, sfunc);
	if (opts && opts->reversesort)
		ft_lstrev(lst);
}
