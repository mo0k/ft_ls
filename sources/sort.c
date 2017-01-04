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

#include <sort.h>

static void		fixe_prev(t_lst_file *lst, t_lst_file *prev)
{
	t_lst_file	*cur;

	cur = lst;
	if (!cur)
		return ;
	cur->prev = prev;
	fixe_prev(cur->next, cur);
}

static void		divise_lst(t_lst_file *source, t_lst_file **dest_1, t_lst_file **dest_2)
{
	t_lst_file	*t_1;
	t_lst_file	*t_2;

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

static void		merge_sort(t_lst_file **lst, t_sort_func sortfunc)
{
	t_lst_file	*current;
	t_lst_file	*lst_1;
	t_lst_file	*lst_2;

	current = *lst;
	if (!current || !current->next || !sortfunc)
		return ;
	divise_lst(current, &lst_1, &lst_2);
	merge_sort(&lst_1, sortfunc);
	merge_sort(&lst_2, sortfunc);
	*lst = sortfunc(lst_1, lst_2); 
	fixe_prev(*lst, NULL);
}

void 	sort(t_lst_file **lst, t_options *options, t_sort_func sortfunc)
{
	if(!lst || !*lst)
		return ;
	if (sortfunc)
		merge_sort(lst, sortfunc);
	if (options && options->reversesort)
		ft_lstrev(lst);
}
